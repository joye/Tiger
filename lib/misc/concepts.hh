#pragma once

#include <concepts>
#include <iterator>

namespace misc
{
  // Concept describing a const Container through which you can iterate
  // Needs methods begin() and end().
  template <typename Container> concept ConstIterable = requires(Container c)
  {
    {
      c.begin() != c.end()
    }
    ->std::same_as<bool>;
    {
      c.begin()
    }
    ->std::convertible_to<typename Container::const_iterator>;
    {
      *c.begin()
    }
    ->std::convertible_to<const typename Container::value_type&>;
  };

  // Concept describing a Container through which you can iterate
  // Needs methods begin() and end().
  template <typename Container>
  concept Iterable = ConstIterable<Container>&& requires(Container c)
  {
    {
      c.begin()
    }
    ->std::same_as<typename Container::iterator>;
    {
      *c.begin()
    }
    ->std::same_as<typename Container::value_type&>;
  };

  // Concept discribing a map.
  // Needs methods lower_bound() and emplace(key, value).
  template <typename M>
  concept Map = requires(M map,
                         const typename M::key_type key,
                         const typename M::mapped_type value,
                         const typename M::iterator i)
  {
    {
      map.lower_bound(key)
    }
    ->std::same_as<typename M::iterator>;

    {map.key_comp()};

    {
      map.emplace(key, value)
    }
    ->std::same_as<std::pair<typename M::iterator, bool>>;

    std::same_as<std::remove_cvref<decltype(*i)>,
                 std::pair<typename M::key_type, typename M::mapped_type>>;
  };

  // Concept describing a ConstIterable but adds a constraint on the value_type
  // the held type should be convertible into T
  template <typename Container, typename T>
  concept ConstIterableType = ConstIterable<Container>&&
    std::convertible_to<typename Container::value_type, T>;

  // Concept describing an Iterable but adds a constraint on the value_type
  // the held type should be convertible into T
  template <typename Container, typename T>
  concept IterableType = Iterable<Container>&&
    std::convertible_to<typename Container::value_type, T>;

  // Concept describing an iterator on a type T
  template <typename Iter, typename T>
  concept Iterator =
    std::forward_iterator<Iter>&& std::same_as<typename Iter::value_type, T>;

} // namespace misc
