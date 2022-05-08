/**
 ** \file ast/chunk-list.cc
 ** \brief Implementation of ast::ChunkList.
 */

#include <ast/chunk-interface.hh>
#include <ast/chunk-list.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  ChunkList::iterator ChunkList::begin() { return chunks_.begin(); }

  ChunkList::iterator ChunkList::end() { return chunks_.end(); }

  ChunkList::const_iterator ChunkList::begin() const { return chunks_.begin(); }

  ChunkList::const_iterator ChunkList::end() const { return chunks_.end(); }

  void ChunkList::push_front(ChunkInterface* d)
  {
    chunks_.emplace_front(d);
    location_.begin = d->location_get().begin;
  }

  void ChunkList::emplace_back(ChunkInterface* d)
  {
    chunks_.emplace_back(d);
    location_.end = d->location_get().end;
  }

  void ChunkList::splice_front(ChunkList& ds)
  {
    chunks_.splice(chunks_.begin(), ds.chunks_get());
  }

  void ChunkList::splice_back(ChunkList& ds)
  {
    chunks_.splice(chunks_.end(), ds.chunks_get());
  }

  ChunkList::ChunkList(const Location& location)
    : Ast(location)
  {}

  ChunkList::ChunkList(const Location& location,
                       const ChunkList::list_type& chunks)
    : Ast(location)
    , chunks_(chunks)
  {}

  ChunkList::~ChunkList() { misc::deep_clear(chunks_); }

  void ChunkList::accept(ConstVisitor& v) const { v(*this); }

  void ChunkList::accept(Visitor& v) { v(*this); }
} // namespace ast
