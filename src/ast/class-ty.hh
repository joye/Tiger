/**
 ** \file ast/class-ty.hh
 ** \brief Declaration of ast::ClassTy.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/name-ty.hh>
#include <ast/ty.hh>

namespace ast
{
  /// ClassTy.
  class ClassTy : public Ty
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a ClassTy node.
    ClassTy(const Location& location, NameTy* super, ChunkList* chunks);
    ClassTy(const ClassTy&) = delete;
    ClassTy& operator=(const ClassTy&) = delete;
    /// Destroy a ClassTy node.
    ~ClassTy() override;
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
    /// Return super class.
    const NameTy& super_get() const;
    /// Return super class.
    NameTy& super_get();
    /// Return list of declarations.
    const ChunkList& chunks_get() const;
    /// Return list of declarations.
    ChunkList& chunks_get();
    /** \} */

  protected:
    /// Super class.
    NameTy* super_;
    /// List of declarations.
    ChunkList* chunks_;
  };
} // namespace ast
#include <ast/class-ty.hxx>
