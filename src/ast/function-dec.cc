/**
 ** \file ast/function-dec.cc
 ** \brief Implementation of ast::FunctionDec.
 */

#include <ast/function-dec.hh>
#include <ast/visitor.hh>

namespace ast
{
  FunctionDec::FunctionDec(const Location& location,
                           misc::symbol name,
                           VarChunk* formals,
                           NameTy* result,
                           Exp* body)
    : Dec(location, name)
    , TypeConstructor()
    , formals_(formals)
    , result_(result)
    , body_(body)
  {}

  FunctionDec::~FunctionDec()
  {
    delete formals_;
    delete result_;
    delete body_;
  }

  void FunctionDec::accept(ConstVisitor& v) const { v(*this); }

  void FunctionDec::accept(Visitor& v) { v(*this); }
} // namespace ast
