/**
 ** \file ast/chunk-interface.hh
 ** \brief Declare the interface for ChunkInterface class.
 */

#pragma once

#include <ast/ast.hh>

namespace ast
{
  /// Declare ChunkInterface
  class ChunkInterface : public Ast
  {
    /** \name Ctors and dtors.
     ** \{ */
  public:
    /// Construct a ChunkInterface
    explicit ChunkInterface(const Location& location);
    /** \} */
  };

} // namespace ast

#include <ast/chunk-interface.hxx>
