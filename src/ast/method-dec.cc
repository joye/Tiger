/**
 ** \file ast/method-dec.cc
 ** \brief Implementation of ast::MethodDec.
 */

#include <ast/method-dec.hh>
#include <ast/visitor.hh>

namespace ast
{
  MethodDec::MethodDec(const Location& location,
                       misc::symbol name,
                       VarChunk* formals,
                       NameTy* result,
                       Exp* body)
    : FunctionDec(location, name, formals, result, body)
  {}

  void MethodDec::accept(ConstVisitor& v) const { v(*this); }

  void MethodDec::accept(Visitor& v) { v(*this); }
} // namespace ast
