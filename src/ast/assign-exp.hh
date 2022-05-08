/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{
  /// AssignExp.
  class AssignExp : public Exp
  {
    // DONE: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IntExp node.
    AssignExp(const Location& location,
              ast::Var* var,
              ast::Exp* exp);
    AssignExp(const AssignExp&) = delete;
    AssignExp& operator=(const AssignExp&) = delete;
    /// Destroy an IntExp node.
    /** \} */

    ~AssignExp()
    {
      delete var_;
      delete exp_;
    }

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    Var* get_var() const
    {
      return var_;
    }

    Exp* get_exp() const
    {
      return exp_;
    }

  protected:
    /// Stored integer value.
    ast::Var* var_;
    ast::Exp* exp_;
  };
} // namespace ast
#include <ast/assign-exp.hxx>
