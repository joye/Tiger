/**
 ** \file misc/list.hh
 ** \brief Declaration of misc::list
 */

#pragma once

#include <misc/vector.hh>

/// Wrappers on misc::vectors to provide functional-style list manipulation.
namespace misc::list
{
  /// Build a list of a \a head and a \a tail.
  template <typename T> vector<T> cons(const T head, const vector<T>& tail);

  /// Get the head and tail of the list. Invert of cons.
  template <typename T> std::pair<T, vector<T>> snoc(const vector<T>& v);

  /// Decompose the list into an array to use structured bindings.
  template <std::size_t Size, typename T>
  std::array<T, Size> decompose(const vector<T>& v);

} // namespace misc::list

#include <misc/list.hxx>
