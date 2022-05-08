/**
 ** \file ast/var.cc
 ** \brief Implementation of ast::Var.
 */

#include <ast/var.hh>
#include <ast/visitor.hh>

namespace ast
{
  Var::Var(const Location& location)
    : Exp(location)
  {}

} // namespace ast
