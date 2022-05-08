/**
 ** \file ast/type-constructor.cc
 ** \brief Implementation of ast::TypeConstructor.
 */

#include <ast/type-constructor.hh>
#include <ast/visitor.hh>

namespace ast
{
  // Done: Some code was deleted here.
  TypeConstructor::TypeConstructor()
    : new_type_(nullptr)
  {}
  TypeConstructor::TypeConstructor(const type::Type* e)
    : new_type_(e)
  {}

  TypeConstructor::~TypeConstructor() { delete new_type_; }

} // namespace ast
