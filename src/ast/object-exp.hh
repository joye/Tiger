/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ObjectExp.
  class ObjectExp : public Exp
  {
    // DONE: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IntExp node.
    ObjectExp(const Location& location, ast::NameTy* type_name);
    ObjectExp(const StringExp&) = delete;
    ObjectExp& operator=(const ObjectExp&) = delete;
    /// Destroy an IntExp node.
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
    /// Return stored integer value.
    ast::NameTy* value_get() const;
    /** \} */

  protected:
    /// Stored integer value.
    ast::NameTy* value_;
  };
} // namespace ast
#include <ast/object-exp.hxx>
