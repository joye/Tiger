/**
 ** \file misc/symbol.cc
 ** \brief Implementation of misc::symbol.
 */

#include <sstream>
#include <string>

#include <misc/symbol.hh>

namespace misc
{
  symbol::symbol(const std::string& s)
    : unique<std::string>(s)
  {}

  symbol::symbol(const char* s)
    : unique<std::string>(std::string(s))
  {}

  symbol symbol::fresh() { return fresh("a"); }

  symbol symbol::fresh(const symbol& s)
  {
    /// Counter of unique symbols.
    static unsigned counter_ = 0;
    std::string str = s.get() + "_" + std::to_string(counter_);
    ++counter_;
    return symbol(str);
  }

} // namespace misc
