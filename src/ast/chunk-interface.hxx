/**
 ** \file ast/chunk-interface.hxx
 ** \brief Inline methods for ast/chunk-interface.hh
 */

#pragma once

#include <ast/chunk-interface.hh>

namespace ast
{
  inline ChunkInterface::ChunkInterface(const Location& location)
    : Ast(location)
  {}

} // namespace ast
