/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <memory>

#include <ast/all.hh>
#include <range/v3/view/iota.hpp>
#include <type/type-checker.hh>
#include <type/types.hh>

namespace type
{
  namespace
  {
    // Try to cast the type into a nil type.
    // If it's not actually a `type::Nil`, return `nullptr`.
    // This allows us to write more clear code like:
    // if (auto nil = to_nil(e.type_get())
    // ...
    const Nil* to_nil(const Type& type)
    {
      return dynamic_cast<const Nil*>(&type.actual());
    }

  } // namespace

  TypeChecker::TypeChecker()
    : super_type()
    , error_()
  {}

  const Type* TypeChecker::type(ast::Typable& e)
  {
    // DONE: Some code was deleted here.
    if (e.get_type())
      {
        return e.get_type();
      }
    else
      {
        e.accept(*this);
        return e.get_type();
      }
  }

  const Record* TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
    // FIXME: Some code was deleted here.
    size_t i = 0;
    while (i < e.size())
      {
        res->field_add(e[i]->name_get(), *type(e[i]->type_name_get()));
        ++i;
      }
    return res;
  }

  const Record* TypeChecker::type(const ast::VarChunk& e)
  {
    auto res = new Record;
    for (const auto& var : e)
      res->field_add(var->name_get(), *type(*var));

    return res;
  }

  const misc::error& TypeChecker::error_get() const { return error_; }

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  void TypeChecker::error(const ast::Ast& ast, const std::string& msg)
  {
    error_ << misc::error::error_type::type << ast.location_get() << ": " << msg
           << std::endl;
  }

  void TypeChecker::type_mismatch(const ast::Ast& ast,
                                  const std::string& exp1,
                                  const Type& type1,
                                  const std::string& exp2,
                                  const Type& type2)
  {
    error_ << misc::error::error_type::type << ast.location_get()
           << ": type mismatch" << misc::incendl << exp1 << " type: " << type1
           << misc::iendl << exp2 << " type: " << type2 << misc::decendl;
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                const Type& type1,
                                const std::string& exp2,
                                const Type& type2)
  {
    // FIXME: Some code was deleted here.
    if (type1.compatible_with(type2.actual()))
      {
        return;
      }
    else
      {
        type_mismatch(ast, exp1, type1, exp2, type2);
      }
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                ast::Typable& type1,
                                const std::string& exp2,
                                ast::Typable& type2)
  {
    // Ensure evaluation order.
    type(type1);
    type(type2);
    // DONE: Some code was deleted here (Check types).
    if (type1.get_type()->compatible_with(type2.get_type()->actual()))
      {
        return;
      }
    else
      {
        type_mismatch(ast, exp1, *type1.get_type(), exp2, *type2.get_type());
      }
  }

  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void TypeChecker::operator()(ast::SimpleVar& e)
  {
    // DONE: Some code was deleted here.
    if (e.def_get())
      {
        type(*e.def_get());
        if (e.def_get()->get_type())
          {
            type_default(e, e.def_get()->get_type());
          }
      }
    else
      {
        if (e.name_get() == "string")
          type_default(e, &String::instance());
        else if (e.name_get() == "int")
          type_default(e, &Int::instance());
      }
  }

  // DONE: Some code was deleted here.

  void TypeChecker::operator()(ast::FieldVar& e)
  {
    type(*e.var_get());
    if (!e.get_type())
      e.type_set(&Void::instance());
    auto ty = dynamic_cast<const Record*>(&e.var_get()->get_type()->actual());
    if (ty)
      {
        if (ty->field_type(e.name_get()))
          e.type_set(ty->field_type(e.name_get()));
        else
          error(e, e.name_get().get() + " is an unknown field");
      }
    else
      {
        error(e, ": this is not a record");
      }
  }

  void TypeChecker::operator()(ast::SubscriptVar& e)
  {
    type(e.var_get());
    type(e.index_get());
    check_type(e.index_get(), "Tab must be indexed with int", Int::instance());
    if (dynamic_cast<const Array*>(&e.var_get().get_type()->actual()))
      e.type_set(&dynamic_cast<const Array*>(&e.var_get().get_type()->actual())
                    ->type_get());
    else
      error(e, ": this is not an array");
  }

  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // Literals.
  void TypeChecker::operator()(ast::NilExp& e)
  {
    auto nil_ptr = std::make_unique<Nil>();
    if (!e.get_type())
      e.type_set(nil_ptr.get());
    created_type_default(e, nil_ptr.release());
  }

  void TypeChecker::operator()(ast::IntExp& e)
  {
    // DONE: Some code was deleted here.
    e.type_set(&Int::instance());
  }

  void TypeChecker::operator()(ast::StringExp& e)
  {
    // DONE: Some code was deleted here.
    e.type_set(&String::instance());
  }

  // Complex values.

  void TypeChecker::operator()(ast::RecordExp& e)
  {
    // If no error occured, check for nil types in the record initialization.
    // If any error occured, there's no need to set any nil types.
    // If there are any record initializations, set the `record_type_`
    // of the `Nil` to the expected type.
    // Done: Some code was deleted here.
    e.get_type_name()->accept(*this);
    auto res = dynamic_cast<const Record*>(
      dynamic_cast<const Named*>(e.get_type_name()->def_get()->get_type())
        ->type_get());
    if (e.get_fieldinits_type()->size() != res->fields_get().size())
      error(e, "named record size != record size");

    size_t i = 0;
    while (i < e.get_fieldinits_type()->size())
      {
        auto g = e.get_fieldinits_type()->at(i);
        type(g->init_get());
        i++;
      }

    e.type_set(res);
  }

  void TypeChecker::operator()(ast::OpExp& e)
  {
    // DONE: Some code was deleted here.

    type(e.left_get());
    type(e.right_get());

    if (to_nil(*e.left_get().get_type()) && to_nil(*e.right_get().get_type()))
      {
        type_mismatch(e, "right op: ", *e.right_get().get_type(),
                      ", left op: ", *e.left_get().get_type());
      }

    if (to_nil(*e.left_get().get_type()))
      {
        if (to_nil(*e.left_get().get_type())
              ->compatible_with(e.right_get().get_type()->actual()))
          {
            to_nil(*e.left_get().get_type())
              ->record_type_set(*e.right_get().get_type());
          }
        else
          {
            type_mismatch(e, "left op", *e.left_get().get_type(),
                          "expected record type but given",
                          *e.right_get().get_type());
          }
      }

    if (to_nil(*e.right_get().get_type()))
      {
        if (to_nil(*e.right_get().get_type())
              ->compatible_with(e.left_get().get_type()->actual()))
          to_nil(*e.right_get().get_type())
            ->record_type_set(*e.left_get().get_type());
        else
          type_mismatch(e, "right op", *e.right_get().get_type(),
                        "expected record but given", *e.left_get().get_type());
      }

    if (!error_)
      {
        // DONE: Some code was deleted here.
        if (!e.left_get().get_type()->compatible_with(
              *e.right_get().get_type()))
          type_mismatch(e, "right op", *e.right_get().get_type(),
                        "but expected", *e.left_get().get_type());
      }
    e.type_set(&Int::instance());
  }

  // DONE: Some code was deleted here.

  void TypeChecker::operator()(ast::AssignExp& e)
  {
    auto e_var = e.get_var();
    type(*e_var);
    auto e_exp = e.get_exp();
    type(*e_exp);
    e.type_set(&Void::instance());

    if (!dynamic_cast<ast::SimpleVar*>(e.get_var())
        || var_read_only_.find(
             dynamic_cast<ast::SimpleVar*>(e.get_var())->def_get())
          == var_read_only_.end())
      {
        if (to_nil(*e_exp->get_type()))
          {
            if (to_nil(e_var->get_type()->actual()))
              {
                to_nil(*e_exp->get_type())
                  ->record_type_set(to_nil(e_var->get_type()->actual())
                                      ->record_type_get()
                                      ->actual());
              }
            else
              {
                to_nil(*e_exp->get_type())
                  ->record_type_set(e_var->get_type()->actual());
              }
          }
        else
          {
            if (e_var->get_type()->actual().compatible_with(
                  e_exp->get_type()->actual()))
              {
                return;
              }
            else
              {
                type_mismatch(e, "assign", *(e_var->get_type()), "but expected",
                              *(e_exp->get_type()));
              }
          }
      }
    else
      {
        error(e, "variable is read only");
      }
  }

  void TypeChecker::operator()(ast::IfExp& e)
  {
    type(*e.get_test());
    auto e_test = e.get_test();
    auto e_then = e.get_thenclause();
    auto e_else = e.get_elseclause();
    check_type(*e_test, "type mismatchs IfExp", Int::instance());
    if (!e_else)
      {
        type(*e_then);
        check_types(e, "then type ", *(e_then->get_type()), "else type",
                    Void::instance());
      }
    else
      {
        type(*e_else);
        check_types(e, "then clause type", *e_then, "else clause type",
                    *e_else);
      }
    e.type_set(e_then->get_type());
  }

  void TypeChecker::operator()(ast::ArrayExp& e)
  {
    type(*e.get_type_name());
    type(*e.get_size());
    type(*e.get_init());
    auto res = dynamic_cast<const Array*>(
      &(e.get_type_name()->def_get()->get_type()->actual()));
    if (!res)
      error(e, " is not a array");
    else
      {
        check_type(*e.get_size(), "type mismatchs ArrayExp", Int::instance());
        check_type(*e.get_init(), "type mismatchs ArrayExp",
                   res->type_get().actual());
      }
    e.type_set(res);
  }
  void TypeChecker::operator()(ast::CallExp& e)
  {
    auto type = e.def_get()->get_type();
    auto args =
      dynamic_cast<const Function*>(type); // function parameters (pattern)
    if (!args)
      error(e, "function is not declared");
    auto formals = (args->formals_get());
    if (formals.fields_get().size() != e.args_get()->size())
      {
        error(e, "wrong number of arguments");
      }
    auto args_p = formals.fields_get();
    size_t i = 0;
    auto args_u = e.args_get(); // parameters user
    while (i < args_u->size())
      {
        (*args_u)[i]->accept(*this);
        if (i >= args_p.size())
          {
            break;
          }
        else if (!args_p[i].type_get().compatible_with(
                   (*args_u)[i]->get_type()->actual()))
          {
            type_mismatch(e, "assigned", *(*args_u)[i]->get_type(), "expected",
                          args_p[i].type_get());
          }
        i++;
      }
    if (i != args_p.size())
      error(e, "missing argument");

    e.type_set(&args->result_get());
  }
  void TypeChecker::operator()(ast::LetExp& e)
  {
    auto b = e.get_body();
    e.get_chunkList()->accept(*this);
    b->accept(*this);
    e.type_set(b->get_type());
  }
  void TypeChecker::operator()(ast::SeqExp& e)
  {
    auto exps = e.get_exps();
    size_t i = 0;
    while (i < exps->size())
      {
        (*exps)[i]->accept(*this);
        i++;
      }
    if (exps->empty())
      e.type_set(&Void::instance());
    else
      e.type_set(exps->back()->get_type());
  }

  // LOOP

  void TypeChecker::operator()(ast::ForExp& e)
  {
    type(e.vardec_get());
    type(e.hi_get());
    check_type(e.vardec_get(), "vardec type mismatchs ForExp", Int::instance());
    check_type(e.hi_get(), "loop type mismatchs ForExp ", Int::instance());
    var_read_only_.insert(&e.vardec_get());
    type(e.body_get());
    check_type(e.body_get(), "body type is not void", Void::instance());
    if (!e.get_type())
      e.type_set(&Void::instance());
  }
  void TypeChecker::operator()(ast::BreakExp& e)
  {
    e.type_set(&Void::instance());
  }

  void TypeChecker::operator()(ast::WhileExp& e)
  {
    type(e.test_get());
    type(e.body_get());
    check_type(e.test_get(), "While condition is not INT", Int::instance());
    check_type(e.body_get(), "While body is not void", Void::instance());
    e.type_set(&Void::instance());
  }

  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/

  void TypeChecker::operator()(ast::FunctionChunk& e)
  {
    chunk_visit<ast::FunctionDec>(e);
  }

  void TypeChecker::operator()(ast::FunctionDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store the type of this function.
  template <>
  void TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
    // DONE: Some code was deleted here.
    if (!e.result_get())
      {
        Function* p;
        p = new Function(type(e.formals_get()), Void::instance());
        e.type_set(p);
        e.created_type_set(p);
      }
    else
      {
        Function* p;
        p = new Function(type(e.formals_get()), *type(*e.result_get()));
        e.type_set(p);
        e.created_type_set(p);
      }
  }

  // Type check this function's body.
  template <>
  void TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    if (e.body_get())
      {
        visit_routine_body<Function>(e);

        // Check for Nil types in the function body.
        if (!error_)
          {
            // DONE: Some code was deleted here.
            auto n = to_nil(*e.body_get()->get_type());
            if (n)
              n->record_type_set(*e.result_get()->get_type());
          }
      }
  }

  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void TypeChecker::operator()(ast::VarDec& e)
  {
    // DONE: Some code was deleted here.
    auto eee = e.init_get();
    auto ggg = e.type_name_get();
    if (eee)
      {
        eee->accept(*this);

        if (!ggg)
          {
            if (to_nil(*eee->get_type()))
              error(e, "initialization is nil with no type specifier");
            else
              e.type_set(eee->get_type());
          }
        else if (!ggg->def_get())
          {
            if (ggg->name_get() == "string")
              e.type_set(&String::instance());
            else if (ggg->name_get() == "int")
              e.type_set(&Int::instance());

            if (!e.get_type()->compatible_with(*eee->get_type()))
              type_mismatch(e, "variable declaration", *(e.get_type()),
                            "variable initialization", *(eee->get_type()));
          }
        else if (ggg->def_get()->get_type()->compatible_with(*eee->get_type()))
          {
            if (auto nil = to_nil(*eee->get_type()))
              nil->record_type_set(ggg->def_get()->get_type()->actual());
            e.type_set(eee->get_type());
          }
        else
          type_mismatch(e, "variable declaration", *ggg->def_get()->get_type(),
                        "variable initialization", *(eee->get_type()));
      }
    else if (ggg)
      {
        ggg->accept(*this);
        e.type_set(ggg->get_type());
      }
    else
      e.type_set(&Void::instance());
  }

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/

  void TypeChecker::operator()(ast::TypeChunk& e)
  {
    chunk_visit<ast::TypeDec>(e);
  }

  void TypeChecker::operator()(ast::TypeDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store this type.
  template <> void TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    // We only process the head of the type declaration, to set its
    // name in E.  A declaration has no type in itself; here we store
    // the type declared by E.
    // DONE: Some code was deleted here.
    Named* ptr = new Named(e.name_get());
    e.created_type_set(ptr);
    e.type_set(ptr);
  }

  // Bind the type body to its name.
  template <> void TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
    // DONE: Some code was deleted here.
    auto name = dynamic_cast<const type::Named*>(e.get_type());
    name->type_set(type(e.ty_get()));
    if (name->sound())
      {
        return;
      }
    else
      {
        error(e, "endless type recursion !!!");
      }
  }

  /*------------------.
  | Visiting /Chunk/. |
  `------------------*/

  template <class D> void TypeChecker::chunk_visit(ast::Chunk<D>& e)
  {
    // DONE: Some code was deleted here.
    size_t i = 0;
    while (i < e.decs_get().size())
      {
        auto dec = e.decs_get()[i];
        visit_dec_header<D>(*dec);
        i++;
      }
    i = 0;
    while (i < e.decs_get().size())
      {
        auto dec = e.decs_get()[i];
        visit_dec_body<D>(*dec);
        i++;
      }
  }

  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  void TypeChecker::operator()(ast::NameTy& e)
  {
    // DONE: Some code was deleted here (Recognize user defined types, and built-in types).

    if (e.name_get() == "int")
      {
        e.type_set(&Int::instance());
        return;
      }
    if (e.name_get() == "string")
      {
        e.type_set(&String::instance());
        return;
      }
    e.type_set(e.def_get()->get_type());
  }

  void TypeChecker::operator()(ast::RecordTy& e)
  {
    // DONE: Some code was deleted here.
    auto a = type(*e.get_fields());
    e.created_type_set(a);
    e.type_set(a);
  }

  void TypeChecker::operator()(ast::ArrayTy& e)
  {
    // DONE: Some code was deleted here.
    e.base_type_get().accept(*this);
    type_default(e, new Array(*e.base_type_get().get_type()));
  }

} // namespace type