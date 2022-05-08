/**
 ** \file ast/class-ty.hxx
 ** \brief Inline methods of ast::ClassTy.
 */

#pragma once

#include <ast/class-ty.hh>

namespace ast
{
  inline const NameTy& ClassTy::super_get() const { return *super_; }
  inline NameTy& ClassTy::super_get() { return *super_; }

  inline const ChunkList& ClassTy::chunks_get() const { return *chunks_; }
  inline ChunkList& ClassTy::chunks_get() { return *chunks_; }

} // namespace ast
