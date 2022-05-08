/**
 ** \file ast/chunk.hxx
 ** \brief Implementation of ast::Chunk.
 */

#pragma once

#include <ast/chunk.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  template <typename D>
  Chunk<D>::Chunk(const Location& location, Ds* decs)
    : ChunkInterface(location)
    , decs_(decs)
  {}

  template <typename D>
  Chunk<D>::Chunk(const Location& location)
    : ChunkInterface(location)
  {}

  template <typename D> Chunk<D>::~Chunk()
  {
    misc::deep_clear(*decs_);
    delete decs_;
  }

  template <typename D> inline void Chunk<D>::accept(Visitor& v) { v(*this); }

  template <typename D> inline void Chunk<D>::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  template <typename D>
  inline constexpr typename Chunk<D>::reference
  Chunk<D>::operator[](size_type pos)
  {
    return decs_->operator[](pos);
  }

  template <typename D>
  inline constexpr typename Chunk<D>::const_reference
  Chunk<D>::operator[](size_type pos) const
  {
    return decs_->operator[](pos);
  }

  template <typename D> inline typename Chunk<D>::Ds& Chunk<D>::decs_get()
  {
    return *decs_;
  }

  template <typename D>
  inline const typename Chunk<D>::Ds& Chunk<D>::decs_get() const
  {
    return *decs_;
  }

  template <typename D> inline typename Chunk<D>::iterator Chunk<D>::begin()
  {
    return decs_->begin();
  }

  template <typename D>
  inline typename Chunk<D>::const_iterator Chunk<D>::begin() const
  {
    return decs_->begin();
  }

  template <typename D> inline typename Chunk<D>::iterator Chunk<D>::end()
  {
    return decs_->end();
  }

  template <typename D>
  inline typename Chunk<D>::const_iterator Chunk<D>::end() const
  {
    return decs_->end();
  }

  template <typename D> inline constexpr bool Chunk<D>::empty() const noexcept
  {
    return decs_->empty();
  }

  template <typename D>
  inline constexpr typename Chunk<D>::iterator
  Chunk<D>::erase(const_iterator pos)
  {
    return decs_->erase(pos);
  }

  template <typename D>
  inline constexpr typename Chunk<D>::iterator
  Chunk<D>::erase(const_iterator first, const_iterator last)
  {
    return decs_->erase(first, last);
  }

  template <typename D> Chunk<D>& Chunk<D>::push_front(D& d)
  {
    location_set(location_get() + d.location_get());
    decs_->insert(decs_->begin(), &d);
    return *this;
  }

  template <typename D> Chunk<D>& Chunk<D>::emplace_back(D& d)
  {
    location_set(location_get() + d.location_get());
    decs_->emplace_back(&d);
    return *this;
  }

} // namespace ast
