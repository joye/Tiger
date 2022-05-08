/**
 ** \file ast/int-exp.cc
 ** \brief Implementation of ast::IntExp.
 */

#include <ast/int-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  IntExp::IntExp(const Location& location, int value)
    : Exp(location)
    , value_(value)
  {}

  void IntExp::accept(ConstVisitor& v) const { v(*this); }

  void IntExp::accept(Visitor& v) { v(*this); }
} // namespace ast
