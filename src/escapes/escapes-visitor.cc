/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>

namespace escapes
{
  // DONE: Some code was deleted here.
  void EscapesVisitor::operator()(ast::VarDec& pop)
  {
    put(&pop);

    pop.set_is_escaped(false);

    if (pop.type_name_get())
    {
      pop.type_name_get()->accept(*this);
    }

    if (pop.init_get())
    {
      pop.init_get()->accept(*this);
    }
  }

  void EscapesVisitor::operator()(ast::FunctionDec& pop)
  {
    scope_begin();

    pop.formals_get().accept(*this);

    if (pop.result_get())
    {
      pop.result_get()->accept(*this);
    }

    if (pop.body_get())
    {
      pop.body_get()->accept(*this);
    }

    scope_end();
  }

  void EscapesVisitor::operator()(ast::SimpleVar& pop)
  {
    auto vardec = get(pop.name_get());

    if (vardec != nullptr)
    {
      vardec->set_is_escaped(true);
    }
  }

  void EscapesVisitor::scope_begin() { var_scope_.scope_begin(); }
  void EscapesVisitor::scope_end() { var_scope_.scope_end(); }

  void EscapesVisitor::put(ast::VarDec* var)
  {
    var_scope_.put(var->name_get(), var);
  }

  inline ast::VarDec* EscapesVisitor::get(misc::symbol sym)
  {
    auto index = var_scope_.stack;
    ast::VarDec* result = nullptr;
    for (auto i = index.rbegin() + 1; i != index.rend() && result == nullptr; i++)
      {
        result = (*i)[sym];
      }
    return result;
  }
} // namespace escapes
