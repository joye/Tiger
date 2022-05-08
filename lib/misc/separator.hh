/**
 ** \file misc/separator.hh
 ** \brief Output containers with a separator between items.
 */

#pragma once

#include <iosfwd>
#include <utility>

namespace misc
{
  template <class C, typename S> class separator
  {
  public:
    separator(const C& c, const S& s);
    std::ostream& operator()(std::ostream& o) const;

  private:
    const C& container_;
    const S& separator_;
  };

  /// Shorthand to create separator(c, s).
  template <class C, typename S>
  separator<C, S> separate(const C& c, const S& s);

  /// Shorthand to create separator(c, '\n').
  template <class C> separator<C, char> separate(const C& c);

  /// Output the separator object \a s on \a ostr.
  template <class C, typename S>
  inline std::ostream& operator<<(std::ostream& ostr, const separator<C, S>& s);

  /// Output the pair \a p on \a ostr.
  /// Usefull if you want to to use a std::pair("something", misc::iendl)
  /// as your separator.
  template <class A, typename B>
  inline std::ostream& operator<<(std::ostream& ostr, const std::pair<A, B>& p);

} // namespace misc

#include <misc/separator.hxx>
