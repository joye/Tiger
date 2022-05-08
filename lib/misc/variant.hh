/**
 ** \file misc/variant.hh
 ** \brief Interface of misc::variant.
 **
 ** misc::variant is a wrapper over std::variant that adds
 ** conversion operators to the original standard variant class.
 ** misc::variant is used just like std::variant, and you
 ** won't be disturbed when using it.
 **/

#pragma once

#include <variant>

namespace misc
{
  // Defining some concepts sepecific to variants:

  // Type T can be converted into another type in Ts,
  // used to set the variant's value.
  template <typename T, typename... Ts>
  concept ContainsTypeSet =
    std::disjunction<std::is_convertible<T, Ts>...>::value;

  // A type in Ts can be converted into T, used to get the variant's value.
  template <typename T, typename... Ts>
  concept ContainsTypeGet =
    std::disjunction<std::is_convertible<Ts, T>...>::value;

  /// Type V is a visitor on each Ts.
  template <typename V, typename... Ts>
  concept Visits = std::conjunction<std::is_invocable<V, Ts>...>::value;

  /// A wrapper over std::variant supporting conversion operators.
  ///
  /// Constraints:
  /// - No type may be const-qualified.
  /// - Each type must be unique.
  /// - The first type must be default constructible.
  ///
  /// Proper declaration form:
  ///   misc::variant<T, T1, ..., Tn>

  template <typename T, typename... Ts>
  class variant : public std::variant<T, Ts...>
  {
  public:
    /// The type of this variant.
    using self_type = variant<T, Ts...>;
    /// Super type.

    using super_type = std::variant<T, Ts...>;

    /// Constructors.
    /// \{
    variant() = default;

    template <typename U>
    requires ContainsTypeSet<U, T, Ts...> variant(const U& rhs);
    /// \}

    template <typename U>
    requires ContainsTypeSet<U, T, Ts...> self_type& operator=(const U&);

    /// \brief Convert this variant to a value of type \a U.
    ///
    /// This conversion relies on std::get.  In particular, if the
    /// conversion fails, a std::bad_variant_access exception is thrown.
    template <typename U> requires ContainsTypeGet<U, T, Ts...> operator U&();

    /// Likewise, const version.
    template <typename U>
    requires ContainsTypeGet<U, T, Ts...> operator const U&() const;

    /** \brief Visit variants of this class.
     ** std::visit does not handle classes inheriting from std::variant, hence
     ** these wrappers.
     ** \{ */
    template <typename V>
    requires Visits<V, T, Ts...> auto visit(V&& visitor) const;

    template <typename V, class... Variants>
    static auto visit(V&& visitor, Variants&&... vars);
    /** \} */
  };

  // Here add variadic template recursion on std::get
  template <typename T, typename... Ts>
  std::ostream& operator<<(std::ostream& os, const variant<T, Ts...>& obj);

  class PrintVisitor
  {
  public:
    PrintVisitor(std::ostream& os)
      : os_(os)
    {}

    template <typename T> std::ostream& operator()(const T& value) const;

  private:
    std::ostream& os_;
  };
} // namespace misc

#include <misc/variant.hxx>
