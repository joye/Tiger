/**
 ** \file misc/fwd.hh
 ** \brief Forward declarations for misc:: items.
 */

#pragma once

namespace misc
{
  // From file-library.hh.
  class file_library;

  // From map.hh.
  template <typename T, typename N> class map;
  // From endomap.hh.
  template <typename T> class endomap;

  // From ref.hh.
  template <typename T> class ref;

  // From select-const.hh.
  template <typename T> struct constify_traits;
  template <typename T> struct id_traits;

  // From symbol.hh.
  class symbol;

  // From xalloc.hh.
  template <class StoredType> class xalloc;

  // From timer.hh
  class timer;

} // namespace misc
