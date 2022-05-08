/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// CallExp.
  class CallExp : public Exp
  {
    // DONE: Some code was deleted here.
  public:
    CallExp(const Location& location, misc::symbol name, exps_type* args);

    CallExp(CallExp&) = delete;
    CallExp& operator=(const CallExp&) = delete;

    void accept(ConstVisitor& v) const override;

    void accept(Visitor& v) override;

    misc::symbol name_get() const
    {
      return name_;
    }

    exps_type* args_get() const
    {
      return args_;
    }

    void args_set(exps_type* args)
    {
      args_ = args;
    }

    const FunctionDec* def_get() const
    {
      return def_;
    }
    /// Return definition site.
    FunctionDec* def_get()
    {
      return def_;
    }
    /// Set definition site.
    void def_set(FunctionDec* def)
    {
      def_ = def;
    }

    void name_set(misc::symbol name)
    {
      name_ = name;
    }

  protected:
    FunctionDec* def_;

    misc::symbol name_;
    exps_type* args_;
  };
} // namespace ast
#include <ast/call-exp.hxx>
