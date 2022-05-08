/**
 ** \file ast/escapable.hh
 ** \brief Declaration of ast::Escapable.
 */

#pragma once

#include <ast/fwd.hh>

namespace ast
{
  /// Escapable.
  class Escapable
  {
    // DONE: Some code was deleted here.
  public:
    Escapable();
    /// Destroy a Escapable node.
    virtual ~Escapable();

    /// Return a boolean for is_escaped.
    bool get_is_escaped() const;
    /// Return a boolean for is_escaped.
    bool get_is_escaped();
    /// set a boolean for is_escaped.
    void set_is_escaped(bool bo);

  private:
    ///the variable is escaped
    bool is_escaped_;
  };
} // namespace ast
#include <ast/escapable.hxx>
