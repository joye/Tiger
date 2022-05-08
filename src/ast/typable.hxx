/**
 ** \file ast/typable.hxx
 ** \brief Inline methods of ast::Typable.
 */

#pragma once

#include <ast/typable.hh>

namespace ast
{
  // Done: Some code was deleted here.
  inline void Typable::type_set(const type::Type* e)
  {
    type_ = e;
  }

  inline const type::Type* Typable::get_type() const
  {
    return type_;
  }
} // namespace ast
