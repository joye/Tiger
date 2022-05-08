/**
 ** \file type/builtin-types.hh
 ** \brief The classes Int, String, Void.
 */
#pragma once

#include <misc/singleton.hh>
#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{
  // Done: Some code was deleted here (Other types : Int, String, Void).
  class Void
    : public type::Type
    , public misc::Singleton<type::Void>
  {
  public:
    Void() = default;
    ~Void() {}
    const Type& actual() const;

    void accept(Visitor& v);
    void accept(ConstVisitor& v) const;
  };

  class String
    : public type::Type
    , public misc::Singleton<type::String>
  {
  public:
    String() = default;
    ~String() {}
    const Type& actual() const;

    void accept(Visitor& v);
    void accept(ConstVisitor& v) const;
  };
  class Int
    : public type::Type
    , public misc::Singleton<type::Int>
  {
  public:
    Int() = default;
    ~Int() {}
    const Type& actual() const;

    void accept(Visitor& v);
    void accept(ConstVisitor& v) const;
  };
} // namespace type
