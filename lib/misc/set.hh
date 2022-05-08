/**
 ** \file misc/set.hh
 ** \brief misc::set: wrapper around std::set.
 **
 ** Set class is a std::set wrapper used to facilitate set
 ** operations such as '+' (union) and '-' and also redefine
 ** functions such as set_union, set_intersection etc. in
 ** order to be more specific and more simple to handle set for our
 ** purpose.
 **/

#pragma once

#include <algorithm>
#include <iosfwd>
#include <set>
#include <vector>
#include <misc/concepts.hh>

namespace misc
{
  template <typename Key,
            typename Compare = std::less<Key>,
            typename Allocator = std::allocator<Key>>
  /**
   ** \brief The class misc::set is wrapper around std::set.
   **
   ** Because Doxygen doesn't handle template
   ** parameters names mix we keep the shorter version,
   ** so K for Key, C for Compare and A for Allocator. */
  class set : public std::set<Key, Compare, Allocator>
  {
  public:
    /// \name typedefs
    /// \{
    using set_type = typename std::set<Key, Compare, Allocator>;

    using iterator = typename set_type::iterator;
    using const_iterator = typename set_type::const_iterator;
    using reverse_iterator = typename set_type::reverse_iterator;
    using const_reverse_iterator = typename set_type::const_reverse_iterator;
    using size_type = typename set_type::size_type;
    using const_reference = typename set_type::const_reference;
    /// \}

    /// \name constructor(s)/destructor.
    /// \{

    explicit set() = default;

    template <typename Iter>
    requires Iterator<Iter, Key> explicit set(Iter first, Iter last);

    /* Useful to convert a container (e.g. std::vector) in misc::set.  */
    template <typename Container>
    requires ConstIterableType<Container, Key> explicit set(const Container v);

    /// \}

    /** \name Element vs. set.
        \{ */

    /// Is \a k part of \a this set?
    bool has(const Key& k) const;

    /** \brief Return the addition of \a data into \a this.
        \a data must not yet be part of \a this. */
    set operator+(const Key& data) const;

    /** \brief Insert \a data in \a this.
        \a data must not yet be part of \a this. */
    set& operator+=(const Key& data);

    /** \brief Return the removal of \a data into \a this.
        \a data must be part of \a this. */
    set operator-(const Key& data) const;

    /** \brief Remove \a data from \a this.
        \a data must be part of \a this. */
    set& operator-=(const Key& data);

    /// \}

    /** \name Set vs. set.
        \{ */

    /// Union with another set \a s.
    // FIXME: Deprecate this use, it ought to be direct sum.
    set operator+(const set<Key, Compare, Allocator>& s) const;

    /// In place union with another set \a s.
    set& operator+=(const set<Key, Compare, Allocator>& s);

    /// Subtraction with another set \a s.
    set operator-(const set<Key, Compare, Allocator>& s) const;

    /// In place subtraction with another set \a s.
    set& operator-=(const set<Key, Compare, Allocator>& s);

    /// Union with another set \a s.
    set operator|(const set& s) const;

    /// In place union with another set \a s.
    set& operator|=(const set& s);

    /// Intersection with another set \a s.
    set operator&(const set& s) const;

    /// In place intersection with another set \a s.
    set& operator&=(const set& s);

    /// \}
  }; // class set

  template <typename Key, typename Compare, typename Allocator>
  inline set<Key, Compare, Allocator>
  set_difference(const set<Key, Compare, Allocator>& s1,
                 const set<Key, Compare, Allocator>& s2);

  template <typename Key, typename Compare, typename Allocator>
  inline set<Key, Compare, Allocator>
  set_intersection(const set<Key, Compare, Allocator>& s1,
                   const set<Key, Compare, Allocator>& s2);

  template <typename Key, typename Compare, typename Allocator>
  inline set<Key, Compare, Allocator>
  set_union(const set<Key, Compare, Allocator>& s1,
            const set<Key, Compare, Allocator>& s2);

  /* Print a human-dump for debugging.

  Warning: this method requires that type Key overloads the operator
  '<<'.  If it is not the case do it or remove set print method
  and << operator (see below).  */
  template <typename Key, typename Compare, typename Allocator>
  inline std::ostream& operator<<(std::ostream& ostr,
                                  const set<Key, Compare, Allocator>& s);

  template <typename Key, typename Compare, typename Allocator>
  inline bool operator%(const Key& k, const set<Key, Compare, Allocator>& s);

} // namespace misc

#include <misc/set.hxx>
