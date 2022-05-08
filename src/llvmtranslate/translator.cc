/**
 ** \file llvmtranslate/translator.cc
 ** \brief Implementation of llvmtranslate::Translator
 */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <llvm/ADT/Triple.h>
#include <llvm/Config/llvm-config.h> // LLVM_VERSION_*
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Verifier.h>  // llvm::verifyFunction
#include <llvm/Support/Host.h> // llvm::sys

#pragma GCC diagnostic pop

#include <ast/all.hh>
#include <llvmtranslate/translator.hh>

namespace llvmtranslate
{
  using namespace std::string_literals;

  namespace
  {
    // Shorthands for integer type and pointer to integer type.
    inline llvm::IntegerType* i32_t(llvm::LLVMContext& ctx)
    {
      return llvm::Type::getInt32Ty(ctx);
    }

    inline llvm::PointerType* i32p_t(llvm::LLVMContext& ctx)
    {
      return llvm::Type::getInt32PtrTy(ctx);
    }

    llvm::AllocaInst* create_alloca(llvm::Function* ll_function,
                                    llvm::Type* ll_type,
                                    const std::string& name)
    {
      // Create an IRBuilder starting at the beginning of the current entry
      // block. LLVM treats allocas as local variables only if they occur at the
      // beginning of a function.
      llvm::IRBuilder<> tmp(&ll_function->getEntryBlock(),
                            ll_function->getEntryBlock().begin());
      return tmp.CreateAlloca(ll_type, nullptr, name);
    }

    // Set default attributes to the functions
    void set_default_attributes(llvm::Function& the_function,
                                const ast::FunctionDec& e)
    {
      the_function.addFnAttr(llvm::Attribute::NoUnwind); // No exceptions in TC
      if (!e.body_get())                                 // Inline primitives
        the_function.addFnAttr(llvm::Attribute::InlineHint);
    }

  } // namespace

  Translator::Translator(llvm::Module& module, escaped_map_type&& escaped)
    : module_{module}
    , ctx_{module_.getContext()}
    , builder_{ctx_}
    , escaped_{std::move(escaped)}
    , type_visitor_{ctx_}
  {
    // The current process triple.
    auto process_triple = llvm::Triple(llvm::sys::getProcessTriple());
    // Set the 32-bit version of the triple.
    module_.setTargetTriple(process_triple.get32BitArchVariant().str());
  }

  void Translator::operator()(const ast::Ast& e)
  {
    translate(e);
    value_ = nullptr;
  }

  llvm::Value* Translator::translate(const ast::Ast& node)
  {
    node.accept(*this);
    return value_;
  }

  llvm::Value* Translator::access_var(const ast::Var& e)
  {
    if (auto var_ast = dynamic_cast<const ast::SimpleVar*>(&e))
      {
        // FIXME: Some code was deleted here.
        auto val = translate(*var_ast->def_get());
        return builder_.CreateLoad(val,
                                   "simpleptr_"s + var_ast->name_get().get());
      }
    else if (auto arr_ast = dynamic_cast<const ast::SubscriptVar*>(&e))
      {
        // FIXME: Some code was deleted here.
        auto arr = translate(arr_ast->var_get());
        auto index_value = translate(arr_ast->index_get());
        return builder_.CreateGEP(arr, index_value,
                                  "subscriptptr_"s + arr->getName().str());
      }
    else if (auto field_ast = dynamic_cast<const ast::FieldVar*>(&e))
      {
        const ast::Var* var = nullptr;
        // FIXME: Some code was deleted here.
        var = field_ast->var_get();
        auto var_val = translate(*var);
        //END
        const type::Record* record_type = nullptr;
        // FIXME: Some code was deleted here.
        record_type = dynamic_cast<const type::Record*>(var->get_type());
        //END
        misc::symbol field_name;
        // FIXME: Some code was deleted here.
        field_name = field_ast->name_get();
        //END
        int index = -1;
        // FIXME: Some code was deleted here (Get the index of the field).
        for (int i = 0; i < record_type->fields_get().size(); ++i)
          {
            if (record_type->fields_get()[i].name_get() == field_name)
              {
                index = i;
                break;
              }
          }
        if (index == -1)
          {
            std::cerr << "Error: Field " << field_name << " not found."
                      << std::endl;
            // HELP
          }
        //END
        // The GEP instruction provides us with safe pointer arithmetics,
        // usually used with records or arrays.
        llvm::Type* record_ltype = nullptr;
        // FIXME: Some code was deleted here (Get a pointer to this structure).
        record_ltype = var_val->getType();
        //END
        return builder_.CreateStructGEP(record_ltype, var_val, index,
                                        "fieldptr_"s + field_name.get());
      }
    else
      unreachable();
  }

  llvm::Value* Translator::init_array(llvm::Value* count_val,
                                      llvm::Value* init_val)
  {
    // Cast everything so that it is conform to the signature of init_array
    // int *init_array(int, int)

    // We need to separate the pointers and the ints.
    // LLVM requires a ptrtoint instruction for pointers
    // and a bitcast for others.
    auto init_val_cast = init_val->getType()->isPointerTy()
      ? builder_.CreatePtrToInt(init_val, i32_t(ctx_), "init_array_ptrtoint")
      : builder_.CreateBitCast(init_val, i32_t(ctx_), "init_array_bitcast");

    // Create the init_array function:
    // First, the arguments (int*, int, int)
    std::vector<llvm::Type*> arg_type{i32_t(ctx_), init_val_cast->getType()};

    // Then, create the FunctionType.
    auto init_array_ltype =
      llvm::FunctionType::get(i32p_t(ctx_), arg_type, false);

    // Get the llvm::Function from the module related to the name and type
    auto init_array_function =
      module_.getOrInsertFunction("tc_init_array", init_array_ltype);

    // Prepare the arguments.
    std::vector<llvm::Value*> arg_vals{count_val, init_val_cast};

    // Create the call.
    auto init_array_call =
      builder_.CreateCall(init_array_function, arg_vals, "init_array_call");

    // Cast the result of the call in the desired type.
    return builder_.CreateBitCast(init_array_call,
                                  init_val->getType()->getPointerTo(),
                                  "init_array_call_cast");
  }

  llvm::Type* Translator::llvm_type(const type::Type& type)
  {
    type_visitor_(type);
    return type_visitor_.llvm_type_get();
  }

  llvm::FunctionType*
  Translator::llvm_function_type(const type::Function& function_type)
  {
    // Prepare the arguments
    std::vector<llvm::Type*> args_types;
    // First, if there are any escaped vars, create ptr arguments for it
    // (Lambda lifting)
    auto escapes_it = escaped_.find(&function_type);
    if (escapes_it != std::end(escaped_))
      {
        auto& escapes = escapes_it->second;
        args_types.reserve(escapes.size()
                           + function_type.formals_get().fields_get().size());
        for (const auto dec : escapes)
          {
            llvm::Type* var_ltype = nullptr;
            // FIXME: Some code was deleted here (Get the llvm type of the VarDec).
            var_ltype = llvm_type(*dec->get_type());
            // END
            args_types.emplace_back(llvm::PointerType::getUnqual(var_ltype));
          }
      }
    else
      args_types.reserve(function_type.formals_get().fields_get().size());

    // Then, the actual arguments
    for (const auto& field : function_type.formals_get())
      args_types.emplace_back(llvm_type(field.type_get()));

    auto result_ltype = llvm_type(function_type.result_get());

    return llvm::FunctionType::get(result_ltype, args_types, false);
  }

  void Translator::operator()(const ast::SimpleVar& e)
  {
    // FIXME: Some code was deleted here.
    value_ = access_var(e);
  }

  void Translator::operator()(const ast::FieldVar& e)
  {
    // FIXME: Some code was deleted here.
    value_ = access_var(e);
  }

  void Translator::operator()(const ast::SubscriptVar& e)
  {
    // FIXME: Some code was deleted here.
    value_ = access_var(e);
  }

  void Translator::operator()(const ast::NilExp& e)
  {
    // FIXME: Some code was deleted here (Get the record_type of the Nil type, and create a null pointer).
    auto record_type = dynamic_cast<const type::Record*>(e.get_type());
    value_ = llvm::ConstantPointerNull::get(
      llvm::PointerType::get(llvm_type(*record_type), 0));
    // END
  }

  void Translator::operator()(const ast::IntExp& e)
  {
    // FIXME: Some code was deleted here (Integers in Tiger are all 32bit signed).
    value_ = llvm::ConstantInt::get(i32_t(ctx_), e.value_get());
  }

  void Translator::operator()(const ast::StringExp& e)
  {
    // FIXME: Some code was deleted here (Strings are translated as `i8*` values, like C's `char*`).
    value_ =
      builder_.CreateGlobalStringPtr(e.value_get(), "string_"s + e.value_get());
  }

  void Translator::operator()(const ast::RecordExp& e)
  {
    // Get the record type
    const type::Record* record_type = nullptr;
    // FIXME: Some code was deleted here.
    record_type = dynamic_cast<const type::Record*>(e.get_type());
    //END

    // Get a pointer to the structure represented by the record type
    // then get the structure from this pointer using getElementType()
    auto struct_ltype = llvm_type(*record_type)->getPointerElementType();

    // The current basic block
    auto current_bb = builder_.GetInsertBlock();

    // The size of the structure and cast it to int
    auto sizeof_val = llvm::ConstantExpr::getSizeOf(struct_ltype);
    sizeof_val = llvm::ConstantExpr::getTruncOrBitCast(sizeof_val, i32_t(ctx_));

    // Generate the instruction calling Malloc
    auto malloc_val =
      llvm::CallInst::CreateMalloc(current_bb, i32_t(ctx_), struct_ltype,
                                   sizeof_val, nullptr, nullptr, "malloccall");

    // Add it using the IR builder
    builder_.Insert(malloc_val, "malloccall");

    // Init the fields
    // FIXME: Some code was deleted here.

    value_ = malloc_val;
  }

  void Translator::operator()(const ast::OpExp& e)
  {
    // FIXME: Some code was deleted here.
    auto l = translate(e.left_get());
    auto r = translate(e.right_get());
    switch (e.oper_get())
      {
      case ast::OpExp::Oper::add:
        value_ = builder_.CreateAdd(l, r, "add");
        break;
      case ast::OpExp::Oper::sub:
        value_ = builder_.CreateSub(l, r, "sub");
        break;
      case ast::OpExp::Oper::mul:
        value_ = builder_.CreateMul(l, r, "mul");
        break;
      case ast::OpExp::Oper::div:
        value_ = builder_.CreateSDiv(l, r, "div");
        break;
      case ast::OpExp::Oper::eq:
        value_ = builder_.CreateICmpEQ(l, r, "eq");
        break;
      case ast::OpExp::Oper::ne:
        value_ = builder_.CreateICmpNE(l, r, "ne");
        break;
      case ast::OpExp::Oper::lt:
        value_ = builder_.CreateICmpSLT(l, r, "lt");
        break;
      case ast::OpExp::Oper::le:
        value_ = builder_.CreateICmpSLE(l, r, "le");
        break;
      case ast::OpExp::Oper::gt:
        value_ = builder_.CreateICmpSGT(l, r, "gt");
        break;
      case ast::OpExp::Oper::ge:
        value_ = builder_.CreateICmpSGE(l, r, "ge");
        break;

      default:
        break;
      }
    //END
    // The comparison instructions returns an i1, and we need an i32, since everything
    // is an i32 in Tiger. Use a zero-extension to avoid this.
    value_ = builder_.CreateZExtOrTrunc(value_, i32_t(ctx_), "op_zext");
  }

  void Translator::operator()(const ast::SeqExp& e)
  {
    // An empty SeqExp is an empty expression, so we should return an int
    // containing 0, since its type is void.
    // FIXME: Some code was deleted here.
    if (e.get_exps()->empty())
      {
        value_ = llvm::ConstantInt::get(i32_t(ctx_), 0);
      }
    else
      {
        super_type::operator()(e);
      }
    //END
  }

  void Translator::operator()(const ast::AssignExp& e)
  {
    // FIXME: Some code was deleted here.
    auto l = translate(*e.get_var());
    auto r = translate(*e.get_exp());
    builder_.CreateStore(r, l);
    value_ = l;
    // END
  }

  void Translator::operator()(const ast::IfExp& e)
  {
    // FIXME: Some code was deleted here (IfExps are handled in a similar way to Kaleidoscope (see LangImpl5.html)).
    auto v = llvm::ConstantInt::get(ctx_, llvm::APInt(1, 0));
    auto* cond_val =
      builder_.CreateICmpNE(translate(*e.get_test()), v, "ifcond");

    auto TheFunction = builder_.GetInsertBlock()->getParent();

    // Create blocks for the then and else cases.  Insert the 'then' block at the
    // end of the function.
    auto* ThenBB = llvm::BasicBlock::Create(ctx_, "then", TheFunction);
    auto* ElseBB = llvm::BasicBlock::Create(ctx_, "else");
    auto* MergeBB = llvm::BasicBlock::Create(ctx_, "ifcont");

    builder_.CreateCondBr(cond_val, ThenBB, ElseBB);

    // Emit then value.
    builder_.SetInsertPoint(ThenBB);
    auto t = e.get_thenclause();
    auto el = e.get_elseclause();
    if (dynamic_cast<const type::Void*>(t->get_type()))
      {
        auto v = new std::vector<ast::Exp*>();
        v->push_back(e.get_thenclause());
        v->push_back(new ast::IntExp{e.location_get(), 0});
        ast::SeqExp* seq = new ast::SeqExp{e.location_get(), v};
        t = seq;
        t->type_set(&type::Int::instance());

        if (el)
          {
            auto v = new std::vector<ast::Exp*>();
            v->push_back(e.get_elseclause());
            v->push_back(new ast::IntExp{e.location_get(), 0});
            ast::SeqExp* seq2 = new ast::SeqExp{e.location_get(), v};
            el = seq2;
          }
        else
          {
            el = new ast::IntExp{e.location_get(), 0};
          }
        el->type_set(&type::Int::instance());
      }

    auto* ThenV = translate(*t);

    /*if (!ThenV)
      return nullptr;*/

    builder_.CreateBr(MergeBB);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    ThenBB = builder_.GetInsertBlock();

    // Emit else block.
    TheFunction->getBasicBlockList().push_back(ElseBB);
    builder_.SetInsertPoint(ElseBB);

    auto* ElseV = translate(*el);

    builder_.CreateBr(MergeBB);
    // codegen of 'Else' can change the current block, update ElseBB for the PHI.
    ElseBB = builder_.GetInsertBlock();

    // Emit merge block.
    TheFunction->getBasicBlockList().push_back(MergeBB);
    builder_.SetInsertPoint(MergeBB);

    llvm::PHINode* PN = builder_.CreatePHI(ThenV->getType(), 2, "iftmp");

    PN->addIncoming(ThenV, ThenBB);
    PN->addIncoming(ElseV, ElseBB);
    value_ = PN;

    // END
  }

  void Translator::operator()(const ast::WhileExp& e)
  {
    // Bb containing the test and the branching
    auto test_bb = llvm::BasicBlock::Create(ctx_, "test", current_function_);
    auto body_bb = llvm::BasicBlock::Create(ctx_, "body", current_function_);
    auto after_bb =
      llvm::BasicBlock::Create(ctx_, "afterloop", current_function_);

    // Save the after block for breaks
    loop_end_[&e] = after_bb;

    // Explicitly fall through from the current block
    builder_.CreateBr(test_bb);

    // Start inside the test BasicBlock
    builder_.SetInsertPoint(test_bb);

    auto v = llvm::ConstantInt::get(ctx_, llvm::APInt(1, 0));
    auto* cond_val = builder_.CreateICmpNE(translate(e.test_get()), v, "eee");

    auto* zero_val =
      llvm::ConstantInt::get(cond_val->getType(), llvm::APInt(1, 0));
    auto cmp_val = builder_.CreateICmpNE(cond_val, zero_val, "loopcond");

    // Create the branching
    builder_.CreateCondBr(cmp_val, body_bb, after_bb);

    // Translate the body inside the body BasicBlock
    builder_.SetInsertPoint(body_bb);
    // Don't store the return value, is should be void.
    translate(e.body_get());

    // Go back to the Test BasicBlock
    builder_.CreateBr(test_bb);

    // Continue after the loop BasicBlock
    builder_.SetInsertPoint(after_bb);
  }

  void Translator::operator()(const ast::BreakExp& e)
  {
    // FIXME: Some code was deleted here.
    auto loop = dynamic_cast<const ast::WhileExp*>(e.loop_get());
    if (loop)
      {
        auto after_bb = loop_end_[loop];
        builder_.CreateBr(after_bb);
      }
    // END
  }

  void Translator::operator()(const ast::ArrayExp& e)
  {
    // Translate the number of elements,
    // fill the array with the default value, then
    // return the pointer to the allocated zone.
    // FIXME: Some code was deleted here (Use `init_array`).
    llvm::Value* count_val = translate(*e.get_size());
    llvm::Value* init_val = nullptr;
    if (e.get_init())
      init_val = translate(*e.get_init());
    else
      init_val = llvm::ConstantInt::getSigned(i32_t(ctx_), 0);
    value_ = init_array(count_val, init_val);
    //END
  }

  void Translator::operator()(const ast::CastExp& e)
  {
    auto exp_val = translate(e.exp_get());
    llvm::Type* ltype = nullptr;
    // FIXME: Some code was deleted here (Destination llvm type).
    ltype = llvm_type(*e.get_type());
    //END

    value_ = builder_.CreateBitCast(exp_val, ltype, "cast_exp");
  }

  void Translator::operator()(const ast::FunctionChunk& e)
  {
    for (const auto& fdec : e)
      visit_function_dec_header(*fdec);

    for (const auto& fdec : e)
      // There is nothing to translate for primitives.
      if (fdec->body_get())
        visit_function_dec_body(*fdec);
  }

  void Translator::visit_function_dec_header(const ast::FunctionDec& e)
  {
    bool is_main = e.name_get() == "_main";
    bool is_primitive = e.body_get() == nullptr;

    // Rename "_main" to "tc_main"
    // FIXME : Quick and dirty
    auto name = is_main ? "tc_main" : e.name_get();

    // Prefix all the primitives with "tc_"
    // FIXME : Quick and dirty
    if (is_primitive)
      name = "tc_" + name.get();

    const type::Type* node_type = nullptr;
    // FIXME: Some code was deleted here.
    node_type = e.get_type();
    //END
    auto& function_type = static_cast<const type::Function&>(*node_type);
    auto function_ltype = llvm_function_type(function_type);

    // Main and primitives have External linkage.
    // Other Tiger functions are treated as "static" functions in C.
    auto linkage = is_main || is_primitive ? llvm::Function::ExternalLinkage
                                           : llvm::Function::InternalLinkage;

    auto the_function =
      llvm::Function::Create(function_ltype, linkage, name.get(), &module_);
    set_default_attributes(*the_function, e);

    auto& escaped = escaped_[&function_type];

    // Name each argument of the function
    for (auto arg_it = the_function->arg_begin();
         arg_it != the_function->arg_end(); ++arg_it)
      {
        auto i = std::distance(the_function->arg_begin(), arg_it);
        auto var = escaped.size() && static_cast<size_t>(i) < escaped.size()
          ? *std::next(escaped_[&function_type].begin(), i)
          : e.formals_get()[i - escaped.size()];

        arg_it->setName(var->name_get().get());
      }
  }

  void Translator::visit_function_dec_body(const ast::FunctionDec& e)
  {
    bool is_main = e.name_get() == "_main";

    auto the_function =
      module_.getFunction(is_main ? "tc_main" : e.name_get().get());

    // Save the old function in case a nested function occurs.
    auto old_insert_point = builder_.saveIP();
    auto old_function = current_function_;
    current_function_ = the_function;

    // Create a new basic block to start the function.
    auto bb = llvm::BasicBlock::Create(ctx_, "entry_"s + e.name_get().get(),
                                       the_function);
    builder_.SetInsertPoint(bb);

    const type::Type* node_type = nullptr;
    // FIXME: Some code was deleted here.
    node_type = e.get_type();
    //END
    auto& function_type = static_cast<const type::Function&>(*node_type);
    auto& escaped = escaped_[&function_type];
    auto& formals = e.formals_get();

    auto arg_it = the_function->arg_begin();

    for (const auto var : escaped)
      {
        locals_[current_function_][var] = &*arg_it;
        ++arg_it;
      }

    // FIXME: Some code was deleted here (Create alloca instructions for each variable).
    for (const auto var : formals)
      {
        auto var_name = var->name_get();
        auto var_ltype = llvm_type(*var->get_type());
        auto var_val =
          builder_.CreateAlloca(var_ltype, nullptr, var_name.get());
        locals_[current_function_][var] = var_val;
      }
    //END
    // FIXME: Some code was deleted here (Create a return instruction).
    if (e.result_get())
      {
        builder_.CreateRet(translate(*e.body_get()));
      }
    else
      {
        translate(*e.body_get());
        builder_.CreateRetVoid();
      }

    //END

    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*the_function);

    // Restore the context of the old function.
    current_function_ = old_function;
    builder_.restoreIP(old_insert_point);
  }

  void Translator::operator()(const ast::CallExp& e)
  {
    // Look up the name in the global module table.
    // If it's a primitive, rename the call to tc_name.
    //
    // Then, add the escaped variables and the rest of the arguments to the
    // list of arguments, and return the correct value.
    // FIXME: Some code was deleted here.
    auto callee_name = e.name_get().get();
    auto callee_ltype = llvm_type(*e.get_type());
    if (!e.def_get()->body_get())
      {
        callee_name = "tc_" + callee_name;
      }
    auto callee = module_.getFunction(callee_name);
    std::vector<llvm::Value*> args;
    for (const auto& arg : *e.args_get())
      args.push_back(translate(*arg));
    value_ = builder_.CreateCall(callee, args);
    //END
  }

  void Translator::operator()(const ast::VarDec& e)
  {
    // Void var types are actually Ints represented by a 0
    // FIXME: Some code was deleted here.    
    auto var_type = llvm_type(*e.get_type());
    value_ = builder_.CreateAlloca(var_type, nullptr, e.name_get().get());
    //END
  }

} // namespace llvmtranslate
