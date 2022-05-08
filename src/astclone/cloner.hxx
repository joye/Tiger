/**
 ** \file astclone/cloner.hxx
 ** \brief Template methods of astclone::Cloner.
 */

#pragma once

#include <ast/libast.hh>
#include <astclone/cloner.hh>

namespace astclone
{
  using namespace ast;

  template <typename T> T* Cloner::recurse(const T& t)
  {
    t.accept(*this);
    T* res = dynamic_cast<T*>(result_);
    assertion(res);
    return res;
  }

  template <typename T> T* Cloner::recurse(const T* const t)
  {
    T* res = nullptr;
    if (t)
      {
        t->accept(*this);
        res = dynamic_cast<T*>(result_);
        assertion(res);
      }
    return res;
  }

  template <typename CollectionType>
  CollectionType* Cloner::recurse_collection(const CollectionType& c)
  {
    auto res = new CollectionType;

    using elt_type = typename CollectionType::value_type;
    for (const elt_type& e : c)
      {
        e->accept(*this);
        auto elt = dynamic_cast<elt_type>(result_);
        assertion(elt);
        res->emplace_back(elt);
      }

    return res;
  }

  template <typename ChunkType> void Cloner::chunk_visit(const ChunkType& e)
  {
    const Location& location = e.location_get();

    // The type of the list contained by this node.
    using elt_type = typename ChunkType::Ds;
    // The cloned list of declarations.
    auto decs = new elt_type;

    for (const typename elt_type::value_type& i : e)
      {
        i->accept(*this);
        auto dec = dynamic_cast<typename elt_type::value_type>(result_);
        assertion(dec);
        decs->emplace_back(dec);
      }
    // The cloned ChunkInterface.
    result_ = new ChunkType(location, decs);
  }

} // namespace astclone
