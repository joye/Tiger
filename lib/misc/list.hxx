/**
 ** \file misc/list.hh
 ** \brief Implementation of misc::list
 */

#pragma once

#include <misc/list.hh>

namespace misc::list
{
  template <class T> inline vector<T> cons(const T head, const vector<T>& tail)
  {
    vector<T> res;

    res.emplace_back(head);
    res.append(tail);

    return res;
  }

  template <class T> inline std::pair<T, vector<T>> snoc(const vector<T>& v)
  {
    precondition(v.size() > 0);

    T head = v[0];
    vector<T> tail(v.begin() + 1, v.end());

    return {head, tail};
  }

  template <std::size_t Size_, typename T>
  inline std::array<T, Size_> decompose(const vector<T>& v)
  {
    precondition(v.size() == Size_);

    std::array<T, Size_> res;
    std::copy(v.begin(), v.end(), res.begin());

    return res;
  }

} // namespace misc::list
