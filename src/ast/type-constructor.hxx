/**
 ** \file ast/type-constructor.hxx
 ** \brief Inline methods of ast::TypeConstructor.
 */

#pragma once

#include <ast/type-constructor.hh>
#include <type/types.hh>

namespace ast
{
  // Done: Some code was deleted here.
  inline void TypeConstructor::created_type_set(const type::Type* e)
  {
    new_type_ = e;
  }
  inline const type::Type* TypeConstructor::created_type_get() const
  {
    return new_type_;
  }
} // namespace ast
