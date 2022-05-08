/**
 ** \file misc/singleton.hh
 ** \brief Generic singleton
 */

#pragma once

namespace misc
{
  template <typename T> class Singleton
  {
    // FIXME: Some code was deleted here.
  public:
    Singleton(const Singleton<T>&) = delete;
    Singleton(Singleton<T>&&) = delete;
    Singleton<T>& operator=(const Singleton<T>&) = delete;
    Singleton<T>& operator=(Singleton<T>&&) = delete;
    static const T& instance()
    {
      static T i;
      return i;
    }

  protected:
    Singleton() = default;
  };
} // namespace misc
