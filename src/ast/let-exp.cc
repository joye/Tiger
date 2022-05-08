/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/let-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // DONE: Some code was deleted here.
  LetExp::LetExp(const Location& location,
                 ast::ChunkList* chunkList,
                 ast::Exp* body)
    : Exp(location)
    , chunkList_(chunkList), body_(body)
  {}

  void LetExp::accept(ConstVisitor& v) const { v(*this); }

  void LetExp::accept(Visitor& v) { v(*this); }
} // namespace ast
