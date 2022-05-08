/**
 ** \file misc/set.hxx
 ** \brief misc::set: wrapper around std::set.
 **/

#pragma once

#include <algorithm>
#include <ostream>

#include <misc/contract.hh>
#include <misc/set.hh>

namespace misc
{
  template <class Key, class Compare, class Allocator>
  template <typename Iter>
  requires Iterator<Iter, Key> inline set<Key, Compare, Allocator>::set(
    Iter first,
    Iter last)
  {
    this->insert(first, last);
  }

  /* Useful to convert a std::vector or other Compare in misc::set.  */
  template <class Key, class Compare, class Allocator>
  template <typename Container>
  requires ConstIterableType<
    Container,
    Key> inline set<Key, Compare, Allocator>::set(const Container v)
  {
    for (const Key& x : v)
      this->insert(x);
  }

  template <class Key, class Compare, class Allocator>
  inline bool set<Key, Compare, Allocator>::has(const Key& k) const
  {
    return set_type::find(k) != this->end();
  }

  /* \brief Return the addition of \a data into \a this.
      \a data must not yet be part of \a this. */
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>
  set<Key, Compare, Allocator>::operator+(const Key& data) const
  {
    precondition(!(data % *this));
    set<Key, Compare, Allocator> res(*this);
    res.insert(data);
    return res;
  }

  /* \brief Insert \a data in \a this.
      \a data must not yet be part of \a this. */
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>&
  set<Key, Compare, Allocator>::operator+=(const Key& data)
  {
    precondition(!(data % *this));
    this->insert(data);
    return *this;
  }

  /* \brief Return the removal of \a data into \a this.
      \a data must be part of \a this. */
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>
  set<Key, Compare, Allocator>::operator-(const Key& data) const
  {
    precondition(data % *this);
    set<Key, Compare, Allocator> res(*this);
    res.erase(data);
    return res;
  }

  /* \brief Remove \a data from \a this.
      \a data must be part of \a this. */
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>&
  set<Key, Compare, Allocator>::operator-=(const Key& data)
  {
    precondition(data % *this);
    this->erase(data);
    return *this;
  }

  // Union with another set \a s.
  // FIXME: Deprecate this use, it ought to be direct sum.
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator> set<Key, Compare, Allocator>::operator+(
    const set<Key, Compare, Allocator>& s) const
  {
    return set_union(*this, s);
  }

  // In place union with another set \a s.
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator+=(
    const set<Key, Compare, Allocator>& s)
  {
    return *this = *this + s;
  }

  // Subtraction with another set \a s.
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator> set<Key, Compare, Allocator>::operator-(
    const set<Key, Compare, Allocator>& s) const
  {
    return set_difference(*this, s);
  }

  // In place subtraction with another set \a s.
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator-=(
    const set<Key, Compare, Allocator>& s)
  {
    *this = *this - s;
    return *this;
  }

  // Union with another set \a s.
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator> set<Key, Compare, Allocator>::operator|(
    const set<Key, Compare, Allocator>& s) const
  {
    return *this + s;
  }

  // In place union with another set \a s.
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator|=(
    const set<Key, Compare, Allocator>& s)
  {
    return *this += s;
  }

  // Intersection with another set \a s.
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator> set<Key, Compare, Allocator>::operator&(
    const set<Key, Compare, Allocator>& s) const
  {
    return set_intersection(*this, s);
  }

  // In place intersection with another set \a s.
  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator&=(
    const set<Key, Compare, Allocator>& s)
  {
    return *this = *this & s;
  }

  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>
  set_difference(const set<Key, Compare, Allocator>& s1,
                 const set<Key, Compare, Allocator>& s2)
  {
    set<Key, Compare, Allocator> res;
    // Specifying the key_comp to use is required: without it, the
    // first set is properly ordered using its own key_comp, but
    // neither the second set nor the resulting set are ordering
    // using it.  Even if s1, s2, and res do use the same Compare!
    std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),
                        inserter(res, res.begin()), s1.key_comp());
    return res;
  }

  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>
  set_intersection(const set<Key, Compare, Allocator>& s1,
                   const set<Key, Compare, Allocator>& s2)
  {
    set<Key, Compare, Allocator> res;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                          inserter(res, res.begin()), s1.key_comp());
    return res;
  }

  template <class Key, class Compare, class Allocator>
  inline set<Key, Compare, Allocator>
  set_union(const set<Key, Compare, Allocator>& s1,
            const set<Key, Compare, Allocator>& s2)
  {
    set<Key, Compare, Allocator> res;
    std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
                   inserter(res, res.begin()), s1.key_comp());
    return res;
  }

  template <class Key, class Compare, class Allocator>
  inline std::ostream& operator<<(std::ostream& ostr,
                                  const set<Key, Compare, Allocator>& s)
  {
    for (auto i = s.begin(); i != s.end();)
      {
        ostr << *i;
        if (++i != s.end())
          ostr << ", ";
      }
    return ostr;
  }

  template <class Key, class Compare, class Allocator>
  inline bool operator%(const Key& k, const set<Key, Compare, Allocator>& s)
  {
    return s.has(k);
  }

} // namespace misc
