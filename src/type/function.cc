/**
 ** \file type/function.cc
 ** \brief Implementation for type/function.hh.
 */

#include <ostream>

#include <range/v3/view/iota.hpp>
#include <type/function.hh>
#include <type/visitor.hh>

namespace type
{
  Function::Function(const Record* formals, const Type& result)
    : result_(result)
  {
    precondition(formals);

    formals_ = formals;
  }

  Function::~Function() { delete formals_; }

  void Function::accept(ConstVisitor& v) const { v(*this); }

  void Function::accept(Visitor& v) { v(*this); }

  // FIXME: Some code was deleted here.

  bool Function::compatible_with(const Type& other) const
  {
    return false;
  }

} // namespace type
