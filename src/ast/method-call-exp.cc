/**
 ** \file ast/method-call-exp.cc
 ** \brief Implementation of ast::MethodCallExp.
 */

#include <ast/method-call-exp.hh>
#include <ast/visitor.hh>

#include "method-call-exp.hh"

namespace ast
{
  // DONE: Some code was deleted here.
  MethodCallExp::MethodCallExp(const Location& location,
                               misc::symbol name,
                               ast::exps_type* args,
                               ast::Var* object)
    : CallExp(location, name, args)
    , name_(name), args_(args), object_(object){};

  void MethodCallExp::accept(ConstVisitor& v) const { v(*this); }

  void MethodCallExp::accept(Visitor& v) { v(*this); }
} // namespace ast
