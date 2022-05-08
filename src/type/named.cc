/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <set>

#include <type/named.hh>
#include <type/visitor.hh>

namespace type
{
  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
    , type_(type)
  {}

  // Done: Some code was deleted here (Inherited functions).
  void Named::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void Named::accept(Visitor& v)
  {
    v(*this);
  }

  // FIXME: Some code was deleted here (Sound).
  bool Named::sound() const
  {
    std::set<const Type*> sept;
    for (auto a = this ; a; a = dynamic_cast<const Named*>(a->type_))
      {
        if (!sept.insert(a).second)
          return false;
      }
    return true;
  }

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Named).
  bool Named::compatible_with(const Type& other) const
  {
    return type_->compatible_with(other);
  }
} // namespace type
