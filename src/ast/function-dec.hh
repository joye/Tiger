/**
 ** \file ast/function-dec.hh
 ** \brief Declaration of ast::FunctionDec.
 */

#pragma once

#include <ast/chunk.hh>
#include <ast/dec.hh>
#include <ast/exp.hh>
#include <ast/name-ty.hh>
#include <ast/type-constructor.hh>
#include <ast/var-dec.hh>

namespace ast
{
  /// FunctionDec.
  class FunctionDec
    : public Dec
    , public TypeConstructor
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a FunctionDec node.
    FunctionDec(const Location& location,
                misc::symbol name,
                VarChunk* formals,
                NameTy* result,
                Exp* body);
    FunctionDec(const FunctionDec&) = delete;
    FunctionDec& operator=(const FunctionDec&) = delete;
    /// Destroy a FunctionDec node.
    ~FunctionDec() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return formal arguments.
    const VarChunk& formals_get() const;
    /// Return formal arguments.
    VarChunk& formals_get();
    /// Return result type.
    const NameTy* result_get() const;
    /// Return result type.
    NameTy* result_get();
    /// Return instructions.
    const Exp* body_get() const;
    /// Return instructions.
    Exp* body_get();
    /// Set instructions.
    void body_set(Exp*);
    /** \} */

  protected:
    /// Formal arguments.
    VarChunk* formals_;
    /// Result type.
    NameTy* result_;
    /// Instructions.
    Exp* body_;
  };
} // namespace ast
#include <ast/function-dec.hxx>
