/**
 ** \file ast/escapable.hxx
 ** \brief Inline methods of ast::Escapable.
 */

#pragma once

#include <ast/escapable.hh>

namespace ast
{
  // DONE: Some code was deleted here.
  inline bool
  Escapable::get_is_escaped() const
  {
    return is_escaped_;
  }
  inline bool
  Escapable::get_is_escaped()
  {
    return is_escaped_;
  }
  inline void
  Escapable::set_is_escaped(bool v)
  {
    this->is_escaped_ = v;
  }
} // namespace ast
