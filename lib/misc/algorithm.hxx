/**
 ** \file misc/algorithm.hxx
 ** \brief Some syntactic sugar to look for things in STL containers.
 */

#pragma once

#include <functional>
#include <ostream>

#include <misc/algorithm.hh>
#include <range/v3/algorithm.hpp>

namespace misc
{
  template <typename Container>
  requires Iterable<Container> void deep_clear(Container& c)
  {
    for (typename Container::value_type& x : c)
      delete x;
    c.clear();
  }

  // Find \a v in the whole \a c.
  template <typename Container>
  requires ConstIterable<Container> inline typename Container::const_iterator
  find(const Container& c, const typename Container::value_type& v)
  {
    return std::find(c.begin(), c.end(), v);
  }

  // Find \a v in the whole \a c.
  template <typename Container>
  requires Iterable<Container> inline typename Container::iterator
  find(Container& c, const typename Container::value_type& v)
  {
    return std::find(c.begin(), c.end(), v);
  }

  // Apply \a f to all the members of \a c, and return it.
  template <typename Container, typename Functor>
  requires ConstIterable<Container> inline Functor& for_each(Container& c,
                                                             Functor& f)
  {
    ranges::for_each(c, std::ref(f));
    return f;
  }

  // Is \a v member of \a c?
  template <typename Container>
  requires ConstIterable<Container> inline bool
  has(const Container& c, const typename Container::value_type& v)
  {
    // We specify the instance to solve a conflict between the
    // two finds above, that compete against each other because
    // the parameter Container can embed a "const".
    return ranges::find(c, v) != c.end();
  }

  template <Map Map>
  typename Map::iterator put(Map& map,
                             const typename Map::key_type& key,
                             const typename Map::mapped_type& value)
  {
    // See ``Efficient STL''.
    auto i = map.lower_bound(key);

    if (i != map.end() && !(map.key_comp()(key, i->first)))
      {
        // Update.
        i->second = value;
        return i;
      }
    else
      {
        // First insertion.
        return map.emplace(key, value).first;
      }
  }

} // namespace misc
