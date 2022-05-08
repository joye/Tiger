/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>

#include <misc/contract.hh>

namespace bind
{
  bool Binder::is_visiting_Chunk = false;
  int Binder::main_count = 0;
  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error& Binder::error_get() const { return error_; }

  // DONE: Some code was deleted here (Error reporting).

  void Binder::break_outside_loop(ast::BreakExp& e)
  {
    error_ << misc::error::error_type::bind << e.location_get()
           << ": break is out of scope " << std::endl;
  }

  void Binder::check_main(const ast::FunctionDec& e)
  {
    if (e.name_get() == "_main")
      {
        main_count++;
        if (main_count > 1)
          {
            error_ << misc::error::error_type::bind
                   << e.location_get() << ": multiple main functions"
                   << std::endl;
          }
      }
  }

  /*----------------.
  | Symbol tables.  |
  `----------------*/

  void Binder::scope_begin()
  {
    // DONE: Some code was deleted here.
    var_scope_.scope_begin();
    type_scope_.scope_begin();
    function_scope_.scope_begin();
  }

  void Binder::scope_end()
  {
    // DONE: Some code was deleted here.
    function_scope_.scope_end();
    var_scope_.scope_end();
    type_scope_.scope_end();
  }

  /*---------.
  | Visits.  |
  `---------*/

  // DONE: Some code was deleted here.
  Binder::Binder() { scope_begin(); }

  Binder::~Binder() { scope_end(); }

  void Binder::operator()(ast::LetExp& e)
  {
    // DONE: Some code was deleted here.
    scope_begin();
    e.get_chunkList()->accept(*this);
    e.get_body()->accept(*this);
    scope_end();
  }

  void Binder::operator()(ast::ForExp& e)
  {
    scope_begin();
    var_scope_.put(e.vardec_get().name_get(), &(e.vardec_get()));
    e.vardec_get().accept(*this);
    e.hi_get().accept(*this);
    loop_scope_.push_back(&e);
    e.body_get().accept(*this);
    loop_scope_.pop_back();
    scope_end();
  }

  void Binder::operator()(ast::WhileExp& e)
  {
    scope_begin();
    is_visiting_Chunk = true;
    e.test_get().accept(*this);
    is_visiting_Chunk = false;
    loop_scope_.push_back(&e);
    e.body_get().accept(*this);
    loop_scope_.pop_back();
    scope_end();
  }

  void Binder::operator()(ast::BreakExp& e)
  {
    if (is_visiting_Chunk)
      break_outside_loop(e);
    else if (loop_scope_.size() == 0)
      break_outside_loop(e);
    else
      {
        auto res = loop_scope_.back();
        e.loop_set(res);
      }
  }

  void Binder::operator()(ast::CallExp& e)
  {
    auto res = function_scope_.get(e.name_get());
    if (res)
      {
        e.def_set(res);
        for (auto& i : *e.args_get())
          i->accept(*this);
      }
    else
      {
        undeclared("function", e);
      }
  }

  void Binder::operator()(ast::SimpleVar& e)
  {
    auto* res = var_scope_.get(e.name_get());
    if (res)
      e.def_set(res);
    else
      undeclared("variable", e);
  }

  void Binder::operator()(ast::NameTy& e)
  {
    auto res = type_scope_.get(e.name_get());
    if (e.name_get().get() == "string" || e.name_get().get() == "int")
      {
        e.def_set(nullptr);
      }
    else
      {
        if (res)
          e.def_set(res);
        else
          undeclared("type", e);
      }
  }

  void Binder::operator()(ast::ChunkList& e)
  {
    for (auto& i : e.chunks_get())
      i->accept(*this);
  }

  /*-------------------.
  | Visiting VarChunk. |
  `-------------------*/

  // DONE: Some code was deleted here.
  void Binder::operator()(ast::VarChunk& e)
  {
    is_visiting_Chunk = true;
    chunk_visit<ast::VarDec>(e);
    is_visiting_Chunk = false;
  }

  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/

  // DONE: Some code was deleted here.
  void Binder::operator()(ast::FunctionChunk& e)
  {
    is_visiting_Chunk = true;
    /*for (auto& i : e.decs_get())
      check_main(*i);*/
    chunk_visit<ast::FunctionDec>(e);
    is_visiting_Chunk = false;
  }

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/
  // DONE: Some code was deleted here.
  void Binder::operator()(ast::TypeChunk& e) { chunk_visit<ast::TypeDec>(e); }

} // namespace bind
