/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// SeqExp.
  class SeqExp : public Exp
  {
    // DONE: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IntExp node.
    SeqExp(const Location& location, ast::exps_type* exps);
    SeqExp(const SeqExp&) = delete;
    SeqExp& operator=(const SeqExp&) = delete;
    /// Destroy an IntExp node.
    /** \} */

    ~SeqExp()
    {
      delete exps_;
    }

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    exps_type* get_exps() const
    {
      return exps_;
    }

  protected:
    /// Stored integer value
    ast::exps_type* exps_;
  };
} // namespace ast
#include <ast/seq-exp.hxx>
