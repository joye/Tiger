/**
 ** \file type/named.hxx
 ** \brief Inline methods for type::Named.
 */
#pragma once

#include <misc/contract.hh>
#include <type/named.hh>

namespace type
{
  inline const Type* Named::type_get() const { return type_; }

  inline void Named::type_set(const Type* type) const { type_ = type; }

  inline misc::symbol Named::name_get() const { return name_; }

  inline void Named::name_set(misc::symbol name) { name_ = name; }

  inline const Type& Named::actual() const
  {
    // Done: Some code was deleted here.
    return type_->actual();
  }

} // namespace type
