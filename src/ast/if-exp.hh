/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  /// IfExp.
  class IfExp : public Exp
  {
    // DONE: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IntExp node.
    IfExp(const Location& location,
          ast::Exp* test,
          ast::Exp* thenclause,
          ast::Exp* elseclause);
    IfExp(const IfExp&) = delete;
    IfExp& operator=(const IfExp&) = delete;

    ~IfExp()
    {
      delete test_;
      delete thenclause_;
      if (elseclause_ != nullptr)
        delete elseclause_;
    }

    /// Destroy an IntExp node.
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    Exp* get_test() const
    {
      return test_;
    }

    Exp* get_thenclause() const
    {
      return thenclause_;
    }

    Exp* get_elseclause() const
    {
      return elseclause_;
    }

  protected:
    /// Stored integer value.
    ast::Exp* test_;
    ast::Exp* thenclause_;
    ast::Exp* elseclause_;
  };
} // namespace ast
#include <ast/if-exp.hxx>
