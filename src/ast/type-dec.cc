/**
 ** \file ast/type-dec.cc
 ** \brief Implementation of ast::TypeDec.
 */

#include <ast/type-dec.hh>
#include <ast/visitor.hh>

namespace ast
{
  TypeDec::TypeDec(const Location& location, misc::symbol name, Ty* ty)
    : Dec(location, name)
    , TypeConstructor()
    , ty_(ty)
  {}

  TypeDec::~TypeDec() { delete ty_; }

  void TypeDec::accept(ConstVisitor& v) const { v(*this); }

  void TypeDec::accept(Visitor& v) { v(*this); }
} // namespace ast
