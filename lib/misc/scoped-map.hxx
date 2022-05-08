/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>
#include <range/v3/view/reverse.hpp>
#include "scoped-map.hh"

namespace misc
{
  // DONE: Some code was deleted here.

  template <typename Key, typename Data> scoped_map<Key, Data>::scoped_map() {}

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::put(const Key& key, const Data& data)
  {
    stack.back()[key] = data;
  }

  template <typename Key, typename Data>
  Data scoped_map<Key, Data>::get(const Key& key) const
  {
    for (auto i = stack.rbegin(); i != stack.rend(); ++i)
      {
        for (auto j = i->begin(); j != i->end(); ++j)
          {
            if (j->first == key)
              return j->second;
          }
      }
    return throw_range_error<Key, Data>();
  }
  template <typename Key, typename Data> void scoped_map<Key, Data>::scope_begin()
  {
    stack.push_back(std::map<Key, Data>());
  }

  template <typename Key, typename Data> void scoped_map<Key, Data>::scope_end()
  {
    stack.pop_back();
  }
  template <typename Key, typename Data>
  void scoped_map<Key, Data>::dump(std::ostream& o) const
  {
    for (auto i = stack.rbegin(); i != stack.rend(); ++i)
      {
        o << "(\n";
        for (auto j = i->begin(); j != i->end(); ++j)
          {
            o << "  " << j->first << " = " << j->second << '\n';
          }
        o << ")\n";
      }
  }

  template <typename Key, typename Data>
  inline std::ostream& operator<<(std::ostream& ostr,
                                  const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace misc
