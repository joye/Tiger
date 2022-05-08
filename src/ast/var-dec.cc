/**
 ** \file ast/var-dec.cc
 ** \brief Implementation of ast::VarDec.
 */

#include <ast/var-dec.hh>
#include <ast/visitor.hh>

namespace ast
{

  VarDec::VarDec(const Location& location,
                 misc::symbol name,
                 NameTy* type_name,
                 Exp* init)
    : Dec(location, name)
    , Escapable()
    , type_name_(type_name)
    , init_(init)
  {}

  VarDec::~VarDec()
  {
    delete type_name_;
    delete init_;
  }

  void VarDec::accept(ConstVisitor& v) const { v(*this); }

  void VarDec::accept(Visitor& v) { v(*this); }
} // namespace ast
