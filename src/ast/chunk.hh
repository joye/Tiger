/**
 ** \file ast/chunk.hh
 ** \brief Declaration of ast::Chunk.
 */

#pragma once

#include <vector>

#include <ast/chunk-interface.hh>

namespace ast
{
  template <typename D>
  /// Abstract a "list of D-declarations" node.
  class Chunk : public ChunkInterface
  {
    /** \name Member types
     ** \{ */
  public:
    /// Define shorthand type for list of D-declarations.
    using Ds = std::vector<D*>;
    /// Define value type
    using value_type = typename Ds::value_type;
    /// Define size type
    using size_type = typename Ds::size_type;
    /// Define reference to value type
    using reference = typename Ds::reference;
    /// Define const reference to value type
    using const_reference = typename Ds::const_reference;
    /// Define shorthand type for D-declations iterator.
    using iterator = typename Ds::iterator;
    /// Define shorthand type for D-declations const iterator.
    using const_iterator = typename Ds::const_iterator;

    /** \} */

    /** \name Ctor & dtor.
     ** \{ */
  public:
    /** \brief Construct an Chunk node with a list of D-declarations.
     ** \param location scanner position informations
     ** \param decs list of D-declarations */
    Chunk(const Location& location, Ds* decs);
    explicit Chunk(const Location& location);

    /** \brief Destroys an Chunk node.
     **
     ** Free list and its content. */
    ~Chunk() override;

    /** \} */

    /** \name Visitors entry point.
     ** \{ */
  public:
    /// Accept a const visitor \a v.
    void accept(Visitor& v) override;

    /// Accept a non-const visitor \a v.
    void accept(ConstVisitor& v) const override;

    /** \} */

    /** \name Accessors.
     ** \{ */
  public: /** \brief Access specified element
     ** /param pos position of the element to return */
    constexpr reference operator[](size_type pos);

    /** \brief Access specified const element
     ** /param pos position of the element to return */
    constexpr const_reference operator[](size_type pos) const;

    /// Access to list of D-declarations (read and write).
    Ds& decs_get();

    /// Access to list of D-declarations (read only).
    const Ds& decs_get() const;

    /** \} */

    /** \name Iterators.
     ** \{ */
  public:
    /// Return an iterator to the begging.
    iterator begin();
    /// Return a const iterator to the begging.
    const_iterator begin() const;

    /// Return an iterator to the end.
    iterator end();
    /// Return a const iterator to the end.
    const_iterator end() const;

    /** \} */

    /** \name Capacity.
     ** \} */
  public:
    /// Checks whether the container is empty.
    [[nodiscard]] constexpr bool empty() const noexcept;

    /** \name Modifiers.
     ** \{ */
  public:
    /** \brief Erase the specified element from the container.
     ** \param pos position of the element to remove. */
    constexpr iterator erase(const_iterator pos);

    /** \brief Erase the specified elements in range from the container.
     ** \param first begin of the range
     ** \param last end of the range */
    constexpr iterator erase(const_iterator first, const_iterator last);

    /** \brief Push \a d in front.
     ** \param d declaration to push */
    Chunk<D>& push_front(D& d);

    /** \brief Push \a d in back.
     ** \param d declaration to push */
    Chunk<D>& emplace_back(D& d);

    /** \} */

    // SWIG 2 does not understand C++11 constructs, such as data
    // member initializers.
#ifndef SWIG
  private:
    Ds* decs_ = new Ds();
#endif
  };

} // namespace ast

#include <ast/chunk.hxx>
