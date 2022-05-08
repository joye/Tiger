/**
 ** \file ast/nil-exp.cc
 ** \brief Implementation of ast::NilExp.
 */

#include <ast/nil-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  NilExp::NilExp(const Location& location)
    : Exp(location)
    , TypeConstructor()
  {}

  void NilExp::accept(ConstVisitor& v) const { v(*this); }

  void NilExp::accept(Visitor& v) { v(*this); }
} // namespace ast
