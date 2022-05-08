/**
 ** \file ast/ast.cc
 ** \brief Implementation of ast::Ast.
 */

#include <ast/ast.hh>
#include <ast/visitor.hh>

namespace ast
{
  Ast::Ast(const Location& location)
    : location_(location)
  {}

} // namespace ast
