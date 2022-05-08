/**
 ** \file ast/exp.cc
 ** \brief Implementation of ast::Exp.
 */

#include <ast/exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  Exp::Exp(const Location& location)
    : Ast(location)
    , Typable()
  {}
} // namespace ast
