/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{
  /// LetExp.
  class LetExp : public Exp
  {
    // DONE: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IntExp node.
    LetExp(const Location& location,
           ast::ChunkList* decs,
           ast::Exp* body);
    LetExp(const LetExp&) = delete;
    LetExp& operator=(const LetExp&) = delete;

    ~LetExp()
    {
      delete chunkList_;
      delete body_;
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

    ChunkList* get_chunkList() const
    {
      return chunkList_;
    }

    Exp* get_body() const
    {
      return body_;
    }

  protected:
    /// Stored integer value.
    ast::ChunkList* chunkList_;
    ast::Exp* body_;
  };
} // namespace ast
#include <ast/let-exp.hxx>
