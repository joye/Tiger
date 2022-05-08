/**
 ** \file misc/separator.hxx
 ** \brief Output containers with a separator between items.
 */

#pragma once

#include <ostream>

#include <misc/deref.hh>
#include <misc/separator.hh>

namespace misc
{
  template <class C, class S>
  inline separator<C, S>::separator(const C& c, const S& s)
    : container_(c)
    , separator_(s)
  {}

  template <class C, typename S>
  inline std::ostream& separator<C, S>::operator()(std::ostream& o) const
  {
    for (auto i = container_.begin(); i != container_.end(); ++i)
      {
        if (i != container_.begin())
          o << separator_;
        o << deref << *i;
      }
    return o;
  }

  template <class C, typename S>
  separator<C, S> separate(const C& c, const S& s)
  {
    return separator<C, S>(c, s);
  }

  template <class C> separator<C, char> separate(const C& c)
  {
    return separate(c, '\n');
  }

  template <class C, typename S>
  inline std::ostream& operator<<(std::ostream& o, const separator<C, S>& s)
  {
    return s(o);
  }

  template <class A, typename B>
  inline std::ostream& operator<<(std::ostream& o, const std::pair<A, B>& p)
  {
    return o << p.first << p.second;
  }
} // namespace misc
