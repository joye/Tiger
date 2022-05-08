/**
 ** \file type/record.cc
 ** \brief Implementation for type/record.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/nil.hh>
#include <type/record.hh>
#include <type/visitor.hh>

namespace type
{
  void Record::accept(ConstVisitor& v) const { v(*this); }

  void Record::accept(Visitor& v) { v(*this); }

  // DONE: Some code was deleted here (Field manipulators).
  const Type* Record::field_type(misc::symbol key) const
  {
    size_t i = 0;
    while (i < fields_.size() && fields_[i].name_get() != key)
      {
        ++i;
      }
    if (i == fields_.size())
      {
        return nullptr;
      }
    return &fields_[i].type_get();
  }

  int Record::field_index(misc::symbol key) const
  {
    for (int i = 0; i < static_cast<int>(fields_.size()); ++i)
      {
        if (fields_[i].name_get() == key)
          return i;
      }
    return -1;
  }

  // DONE: Some code was deleted here (Special implementation of "compatible_with" for Record).
  bool Record::compatible_with(const Type& other) const
  {
    if ((dynamic_cast<const Nil*>(&other)) || &other == this)
      {
        return true;
      }
    return false;
  }

} // namespace type
