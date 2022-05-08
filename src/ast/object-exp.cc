/**
 ** \file ast/object-exp.cc
 ** \brief Implementation of ast::ObjectExp.
 */

#include <ast/object-exp.hh>
#include <ast/visitor.hh>

#include "object-exp.hh"

namespace ast
{
  // DONE: Some code was deleted here.
  ObjectExp::ObjectExp(const Location& location, ast::NameTy* value)
    : Exp(location)
    , value_(value)
  {}

  void ObjectExp::accept(ConstVisitor& v) const { v(*this); }

  void ObjectExp::accept(Visitor& v) { v(*this); }

  ast::NameTy* ObjectExp::value_get() const { return value_; }

} // namespace ast
