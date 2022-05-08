/**
 ** \file overload/over-table.hxx
 ** \brief Inline methods and template implementations for overload/over-table.hh.
 */

#pragma once

#include <ostream>

#include <overload/over-table.hh>
#include <range/v3/view/reverse.hpp>

namespace overload
{
  template <typename T> OverTable<T>::OverTable()
  {
    oversymtab_.emplace_back();
  }

  template <typename T> void OverTable<T>::put(misc::symbol key, T& value)
  {
    oversymtab_.back().emplace(key, &value);
  }

  template <typename T>
  typename OverTable<T>::range_type OverTable<T>::get(misc::symbol key)
  {
    precondition(!oversymtab_.empty());
    auto& map = oversymtab_.back();
    return map.equal_range(key);
  }

  template <typename T> void OverTable<T>::scope_begin()
  {
    oversymtab_.emplace_back(oversymtab_.back());
  }

  template <typename T> void OverTable<T>::scope_end()
  {
    precondition(!oversymtab_.empty());
    oversymtab_.pop_back();
  }

  template <typename T>
  std::ostream& OverTable<T>::dump(std::ostream& ostr) const
  {
    ostr << "<overTable>\n";
    for (const auto& m : oversymtab_ | ranges::views::reverse)
      {
        ostr << "<scope>\n";
        for (const auto& im : m)
          ostr << im.first << " : " << im->second.size() << '\n';
        ostr << "</scope>\n";
      }
    return ostr << "</overTable>\n";
  }

  template <typename T>
  std::ostream& operator<<(std::ostream& ostr, const OverTable<T>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace overload
