/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ArrayExp.
  class ArrayExp : public Exp
  {
    // DONE: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IntExp node.
    ArrayExp(const Location& location,
             ast::NameTy* type_name,
             ast::Exp* size,
             ast::Exp* init);
    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;
    /// Destroy an IntExp node.
    /** \} */

    ~ArrayExp()
    {
      delete type_name_;
      delete size_;
      delete init_;
    }

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    NameTy* get_type_name() const
    {
      return type_name_;
    }

    Exp* get_size() const
    {
      return size_;
    }

    Exp* get_init() const
    {
      return init_;
    }

  protected:
    /// Stored integer value.
    ast::NameTy* type_name_;
    ast::Exp* size_;
    ast::Exp* init_;
  };
} // namespace ast
#include <ast/array-exp.hxx>
