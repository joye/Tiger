/**
 ** \file ast/simple-var.cc
 ** \brief Implementation of ast::SimpleVar.
 */

#include <ast/simple-var.hh>
#include <ast/visitor.hh>

namespace ast
{
  SimpleVar::SimpleVar(const Location& location, misc::symbol name)
    : Var(location)
    , name_(name)
  {}

  void SimpleVar::accept(ConstVisitor& v) const { v(*this); }

  void SimpleVar::accept(Visitor& v) { v(*this); }
} // namespace ast
