/**
 ** \file ast/call-exp.cc
 ** \brief Implementation of ast::CallExp.
 */

#include <ast/call-exp.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  // DONE: Some code was deleted here.
  CallExp::CallExp(const Location& location,
                   misc::symbol name,
                   ast::exps_type* args)
    : Exp(location)
    , name_(name)
    , args_(args)
  {}

  void CallExp::accept(ConstVisitor& v) const { v(*this); }

  void CallExp::accept(Visitor& v) { v(*this); }
} // namespace ast
