/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// FieldVar.
  class FieldVar : public Var
  {
    // DONE: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IntExp node.
    FieldVar(const Location& location,
             Var* var,
             misc::symbol name);
    FieldVar(const FieldVar&) = delete;
    FieldVar& operator=(const FieldVar&) = delete;
    /// Destroy an IntExp node.
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    Var* var_get() const
    {
      return var_;
    }

    misc::symbol name_get() const
    {
      return name_;
    }

  protected:
    Var* var_;
    misc::symbol name_;

  };
} // namespace ast
#include <ast/field-var.hxx>
