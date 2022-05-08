/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// RecordExp.
  class RecordExp : public Exp
  {
    // DONE: Some code was deleted here.
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IntExp node.
    RecordExp(const Location& location,
              NameTy* type_name,
              fieldinits_type* fields);
    RecordExp(const RecordExp&) = delete;
    RecordExp& operator=(const RecordExp&) = delete;

    ~RecordExp()
    {
        delete type_name_;
        delete fields_;
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

    NameTy* get_type_name() const
    {
      return type_name_;
    }

    fieldinits_type* get_fieldinits_type() const
    {
        return fields_;
    }

  protected:
    /// Stored integer value.
    NameTy* type_name_;
    fieldinits_type* fields_;
  };
} // namespace ast
#include <ast/record-exp.hxx>
