/**
 ** \file astclone/cloner.cc
 ** \brief Implementation of astclone::Cloner.
 */

#include <ast/all.hh>
#include <astclone/cloner.hh>
#include <misc/symbol.hh>

namespace astclone
{
  using namespace ast;

  Cloner::Cloner()
    : result_(nullptr)
  {}

  Ast* Cloner::result_get() { return result_; }

  void Cloner::operator()(const ast::ArrayExp& e)
  {
    // Done: Some code was deleted here.

    result_ = new ArrayExp(e.location_get(), recurse(*e.get_type_name()),
                           recurse(*e.get_size()), recurse(*e.get_init()));
  }

  void Cloner::operator()(const ast::ArrayTy& e)
  {
    const Location& location = e.location_get();
    NameTy* base_type = recurse(e.base_type_get());
    result_ = new ArrayTy(location, base_type);
  }

  void Cloner::operator()(const ast::AssignExp& e)
  {
    // Done: Some code was deleted here.
    result_ = new AssignExp(e.location_get(), recurse(*e.get_var()),
                            recurse(*e.get_exp()));
  }

  void Cloner::operator()(const ast::BreakExp& e)
  {
    // Done: Some code was deleted here.
    result_ = new BreakExp(e.location_get());
  }

  void Cloner::operator()(const ast::CallExp& e)
  {
    // Done: Some code was deleted here.
    auto* exps = new exps_type();
    for (auto a : *e.args_get())
      {
        exps->push_back(recurse(*a));
      }
    result_ = new CallExp(e.location_get(), e.name_get(), exps);
  }

  void Cloner::operator()(const ast::CastExp& e)
  {
    const Location& location = e.location_get();
    Exp* exp = recurse(e.exp_get());
    Ty* ty = recurse(e.ty_get());
    result_ = new CastExp(location, exp, ty);
  }

  void Cloner::operator()(const ast::ChunkList& e)
  {
    const Location& location = e.location_get();
    ChunkList::list_type chunks = *recurse_collection(e.chunks_get());
    result_ = new ChunkList(location, chunks);
  }

  void Cloner::operator()(const ast::ClassTy& e)
  {
    const Location& location = e.location_get();
    NameTy* super = recurse(e.super_get());
    ChunkList* chunks = recurse(e.chunks_get());
    result_ = new ClassTy(location, super, chunks);
  }

  void Cloner::operator()(const ast::Field& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    NameTy* type_name = recurse(e.type_name_get());
    result_ = new Field(location, name, type_name);
  }

  void Cloner::operator()(const ast::FieldInit& e)
  {
    result_ =
      new FieldInit(e.location_get(), e.name_get(), recurse(e.init_get()));
  }

  void Cloner::operator()(const ast::FieldVar& e)
  {
    // Done: Some code was deleted here.
    result_ =
      new FieldVar(e.location_get(), recurse(*e.var_get()), e.name_get());
  }

  void Cloner::operator()(const ast::ForExp& e)
  {
    const Location& location = e.location_get();
    VarDec* vardec = recurse(e.vardec_get());
    Exp* hi = recurse(e.hi_get());
    Exp* body = recurse(e.body_get());
    result_ = new ForExp(location, vardec, hi, body);
  }

  void Cloner::operator()(const ast::FunctionDec& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    VarChunk* formals = recurse(e.formals_get());
    NameTy* result = recurse(e.result_get());
    Exp* body = recurse(e.body_get());
    auto fundec = new FunctionDec(location, name, formals, result, body);
    result_ = fundec;
  }

  void Cloner::operator()(const ast::IfExp& e)
  {
    // Done: Some code was deleted here.
    result_ = new IfExp(
      e.location_get(), recurse(*e.get_test()), recurse(*e.get_thenclause()),
      e.get_elseclause() ? recurse(*e.get_elseclause()) : nullptr);
  }

  void Cloner::operator()(const ast::IntExp& e)
  {
    result_ = new IntExp(e.location_get(), e.value_get());
  }

  void Cloner::operator()(const ast::LetExp& e)
  {
    // Done: Some code was deleted here.
    result_ = new LetExp(e.location_get(), recurse(*e.get_chunkList()),
                         recurse(*e.get_body()));
  }

  void Cloner::operator()(const ast::MethodCallExp& e)
  {
    // FIXME: Some code was deleted here. (Optional)
    auto* exps = new exps_type();
    for (auto a : *e.args_get())
      {
        exps->push_back(recurse(*a));
      }
    result_ = new CallExp(e.location_get(), e.name_get(), exps);
  }

  void Cloner::operator()(const ast::MethodDec& e)
  {
    result_ =
      new MethodDec(e.location_get(), e.name_get(), recurse(e.formals_get()),
                    recurse(e.result_get()), recurse(e.body_get()));
  }

  void Cloner::operator()(const ast::NameTy& e)
  {
    result_ = new NameTy(e.location_get(), e.name_get());
  }

  void Cloner::operator()(const ast::NilExp& e)
  {
    result_ = new NilExp(e.location_get());
  }

  void Cloner::operator()(const ast::ObjectExp& e)
  {
    // FIXME: Some code was deleted here. (Optional)
    (void)e;
  }

  void Cloner::operator()(const ast::OpExp& e)
  {
    const Location& location = e.location_get();
    Exp* left = recurse(e.left_get());
    OpExp::Oper oper = e.oper_get();
    Exp* right = recurse(e.right_get());
    result_ = new OpExp(location, left, oper, right);
  }

  void Cloner::operator()(const ast::RecordExp& e)
  {
    // Done: Some code was deleted here.
    fieldinits_type* fields = new fieldinits_type();
    for (auto a : *e.get_fieldinits_type())
      {
        fields->push_back(recurse(*a));
      }

    result_ =
      new RecordExp(e.location_get(), recurse(*e.get_type_name()), fields);
  }

  void Cloner::operator()(const ast::RecordTy& e)
  {
    // Done: Some code was deleted here.
    fields_type* fields = new fields_type();
    for (auto a : *e.get_fields())
      {
        fields->push_back(recurse(*a));
      }
    result_ = new RecordTy(e.location_get(), fields);
  }

  void Cloner::operator()(const ast::SeqExp& e)
  {
    // Done: Some code was deleted here.
    exps_type* exps = recurse_collection(*e.get_exps()); //new exps_type();
    //for (auto a : *e.get_exps())
    //  {
    //    exps->push_back(recurse(*a));
    //  }
    result_ = new SeqExp(e.location_get(), exps);
  }

  void Cloner::operator()(const ast::SimpleVar& e)
  {
    result_ = new SimpleVar(e.location_get(), e.name_get());
  }

  void Cloner::operator()(const ast::StringExp& e)
  {
    // Done: Some code was deleted here.
    result_ = new StringExp(e.location_get(), e.value_get());
  }

  void Cloner::operator()(const ast::SubscriptVar& e)
  {
    const Location& location = e.location_get();
    Var* var = recurse(e.var_get());
    Exp* index = recurse(e.index_get());
    result_ = new SubscriptVar(location, var, index);
  }

  void Cloner::operator()(const ast::TypeDec& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    Ty* ty = recurse(e.ty_get());
    result_ = new TypeDec(location, name, ty);
  }

  void Cloner::operator()(const ast::VarDec& e)
  {
    // Done: Some code was deleted here (Cloned node instantiation).
    result_ = new VarDec(e.location_get(), e.name_get(),
                         recurse(e.type_name_get()), recurse(e.init_get()));
  }

  void Cloner::operator()(const ast::WhileExp& e)
  {
    const Location& location = e.location_get();
    Exp* test = recurse(e.test_get());
    Exp* body = recurse(e.body_get());
    result_ = new WhileExp(location, test, body);
  }

  void Cloner::operator()(const ast::FunctionChunk& e)
  {
    chunk_visit<ast::FunctionChunk>(e);
  }

  void Cloner::operator()(const ast::MethodChunk& e)
  {
    // FIXME: Some code was deleted here.
    chunk_visit<ast::MethodChunk>(e);
  }

  void Cloner::operator()(const ast::TypeChunk& e)
  {
    // FIXME: Some code was deleted here.
    chunk_visit<ast::TypeChunk>(e);
  }

  void Cloner::operator()(const ast::VarChunk& e)
  {
    // FIXME: Some code was deleted here.
    chunk_visit<ast::VarChunk>(e);
  }

} // namespace astclone
