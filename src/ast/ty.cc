/**
 ** \file ast/ty.cc
 ** \brief Implementation of ast::Ty.
 */

#include <ast/ty.hh>
#include <ast/visitor.hh>

namespace ast
{
  Ty::Ty(const Location& location)
    : Ast(location)
    , Typable()
    , TypeConstructor()
  {}

} // namespace ast
