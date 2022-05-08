/**
 ** \file type/array.cc
 ** \brief Implementation for type/array.hh.
 */

#include <type/array.hh>
#include <type/visitor.hh>

namespace type
{
  // Done: Some code was deleted here.
  Array::Array(const Type& type)
    : type_(type)
  {}

  void Array::accept(ConstVisitor& v) const
  {
    v(*this);
  }
  /// Accept a non-const visitor \a v.
  void Array::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace type
