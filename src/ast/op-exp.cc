/**
 ** \file ast/op-exp.cc
 ** \brief Implementation of ast::OpExp.
 */

#include <ast/op-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  OpExp::OpExp(const Location& location,
               Exp* left,
               OpExp::Oper oper,
               Exp* right)
    : Exp(location)
    , left_(left)
    , oper_(oper)
    , right_(right)
  {}

  OpExp::~OpExp()
  {
    delete left_;
    delete right_;
  }

  void OpExp::accept(ConstVisitor& v) const { v(*this); }

  void OpExp::accept(Visitor& v) { v(*this); }
} // namespace ast

std::string str(ast::OpExp::Oper oper)
{
  // DONE: Some code was deleted here.
  switch (oper)
    {
    case ast::OpExp::Oper::add:
      return "+";
    case ast::OpExp::Oper::sub:
      return "-";
    case ast::OpExp::Oper::div:
      return "/";
    case ast::OpExp::Oper::mul:
      return "*";
    case ast::OpExp::Oper::eq:
      return "=";
    case ast::OpExp::Oper::ne:
      return "<>";
    case ast::OpExp::Oper::lt:
      return "<";
    case ast::OpExp::Oper::le:
      return "<=";
    case ast::OpExp::Oper::gt:
      return ">";
    case ast::OpExp::Oper::ge:
      return ">=";
    default:
      return "";
    }
}
