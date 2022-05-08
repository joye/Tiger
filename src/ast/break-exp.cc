/**
 ** \file ast/break-exp.cc
 ** \brief Implementation of ast::BreakExp.
 */

#include <ast/break-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // DONE: Some code was deleted here.
  BreakExp::BreakExp(const Location& location)
    : Exp(location)
  {}

  void BreakExp::accept(ConstVisitor& v) const { v(*this); }

  void BreakExp::accept(Visitor& v) { v(*this); }

  const Exp* BreakExp::loop_get() const { return loop_; }

  Exp* BreakExp::loop_get() { return loop_; }

  void BreakExp::loop_set(Exp* loop) { loop_ = loop; }
} // namespace ast
