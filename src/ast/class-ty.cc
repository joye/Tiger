/**
 ** \file ast/class-ty.cc
 ** \brief Implementation of ast::ClassTy.
 */

#include <ast/class-ty.hh>
#include <ast/visitor.hh>

namespace ast
{
  ClassTy::ClassTy(const Location& location, NameTy* super, ChunkList* chunks)
    : Ty(location)
    , super_(super)
    , chunks_(chunks)
  {}

  ClassTy::~ClassTy() { delete chunks_; }

  void ClassTy::accept(ConstVisitor& v) const { v(*this); }

  void ClassTy::accept(Visitor& v) { v(*this); }
} // namespace ast
