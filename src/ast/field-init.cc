/**
 ** \file ast/field-init.cc
 ** \brief Implementation of ast::FieldInit.
 */

#include <ast/field-init.hh>
#include <ast/visitor.hh>

namespace ast
{
  FieldInit::FieldInit(const Location& location, misc::symbol name, Exp* init)
    : Ast(location)
    , name_(name)
    , init_(init)
  {}

  FieldInit::~FieldInit() { delete init_; }

  void FieldInit::accept(ConstVisitor& v) const { v(*this); }

  void FieldInit::accept(Visitor& v) { v(*this); }
} // namespace ast
