/**
 ** \file ast/assign-exp.cc
 ** \brief Implementation of ast::AssignExp.
 */

#include <ast/assign-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // DONE: Some code was deleted here.
  AssignExp::AssignExp(const Location& location,
                       ast::Var* var,
                       ast::Exp* exp)
    : Exp(location)
    , var_(var), exp_(exp)
  {}

  void AssignExp::accept(ConstVisitor& v) const { v(*this); }

  void AssignExp::accept(Visitor& v) { v(*this); }
} // namespace ast
