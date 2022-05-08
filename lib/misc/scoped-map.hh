/**
 ** \file misc/scoped-map.hh
 ** \brief Declaration of misc::scoped_map.
 **
 ** This implements a stack of dictionnaries.  Each time a scope is
 ** opened, a new dictionnary is added on the top of the stack; the
 ** dictionary is removed when the scope is closed.  Lookup of keys
 ** is done in the last added dictionnary first (LIFO).
 **
 ** In particular this class is used to implement symbol tables.
 **/

#pragma once

#include <map>
#include <vector>
#include <ostream>

namespace misc
{
  template <typename Key, typename Data> class scoped_map
  {
    // DONE: Some code was deleted here.
  public:
    // Vars
    std::vector<std::map<Key, Data>> stack;

    // Ctor / Dtor

    scoped_map();
    ~scoped_map() = default;
    // Methods
    void dump(std::ostream& o) const;
    // in scope
    void put(const Key& key, const Data& data);
    Data get(const Key& key) const;
    // scope
    void scope_begin();
    void scope_end();
  };

  template <typename Key, typename Data>
  std::ostream& operator<<(std::ostream& ostr,
                           const scoped_map<Key, Data>& tbl);

  // DONE: Some code was deleted here.
  //Error function.
  template <typename Key, typename Data>
  std::enable_if_t<std::is_pointer<Data>::value, Data>
  throw_range_error()
  {
    return nullptr;
  }

  template <typename Key, typename Data>
  std::enable_if_t<!std::is_pointer<Data>::value, Data>
  throw_range_error()
  {
    throw(std::range_error("Impossible to find element in the current scope."));
  }

} // namespace misc

#include <misc/scoped-map.hxx>
