/**
 ** \file ast/chunk-list.hxx
 ** \brief Inline methods of ast::ChunkList.
 */

#pragma once

#include <ast/chunk-list.hh>

namespace ast
{
  inline const ChunkList::list_type& ChunkList::chunks_get() const
  {
    return chunks_;
  }
  inline ChunkList::list_type& ChunkList::chunks_get() { return chunks_; }

} // namespace ast
