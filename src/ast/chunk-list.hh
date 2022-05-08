/**
 ** \file ast/chunk-list.hh
 ** \brief Declaration of ast::ChunkList.
 */

#pragma once

#include <ast/ast.hh>

namespace ast
{
  /// ChunkList.
  class ChunkList : public Ast
  {
  public:
    using list_type = std::list<ChunkInterface*>;
    using iterator = list_type::iterator;
    using const_iterator = list_type::const_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    /// Prepend \a d.
    void push_front(ChunkInterface* d);
    /// Append \a d.
    void emplace_back(ChunkInterface* d);

    /// Splice the content of \a ds in front of this list.
    void splice_front(ChunkList& ds);
    /// Splice the content of \a ds at the back this list.
    void splice_back(ChunkList& ds);

    /// Construct a ChunkList node.
    ChunkList(const Location& location);

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a ChunkList node.
    ChunkList(const Location& location, const ChunkList::list_type& chunks);
    ChunkList(const ChunkList&) = delete;
    ChunkList& operator=(const ChunkList&) = delete;
    /// Destroy a ChunkList node.
    ~ChunkList() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return declarations.
    const ChunkList::list_type& chunks_get() const;
    /// Return declarations.
    ChunkList::list_type& chunks_get();
    /** \} */

  protected:
    /// Declarations.
    ChunkList::list_type chunks_;
  };
} // namespace ast
#include <ast/chunk-list.hxx>
