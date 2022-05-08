/**
 ** \file type/builtin-types.cc
 ** \brief Implementation for type/builtin-types.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/visitor.hh>

namespace type
{
  // Done: Some code was deleted here (Int, String, Void).

  void Void::accept(ConstVisitor& v) const { v(*this); }
  void Void::accept(Visitor& v) { v(*this); }
  const Type& Void::actual() const { return Void::instance(); }

  void String::accept(ConstVisitor& v) const { v(*this); }
  void String::accept(Visitor& v) { v(*this); }
  const Type& String::actual() const { return String::instance(); }

  void Int::accept(ConstVisitor& v) const { v(*this); }
  void Int::accept(Visitor& v) { v(*this); }
  const Type& Int::actual() const { return Int::instance(); }
} // namespace type
