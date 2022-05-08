/**
 ** \file ast/name-ty.cc
 ** \brief Implementation of ast::NameTy.
 */

#include <ast/name-ty.hh>
#include <ast/visitor.hh>

namespace ast
{
  NameTy::NameTy(const Location& location, misc::symbol name)
    : Ty(location)
    , name_(name)
  {}

  void NameTy::accept(ConstVisitor& v) const { v(*this); }

  void NameTy::accept(Visitor& v) { v(*this); }
} // namespace ast
