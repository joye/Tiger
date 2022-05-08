/**
 ** \file misc/lambda-visitor.hh
 ** \brief Declaration of misc::LambdaVisitor.
 **/

#pragma once

namespace misc
{
  /** \brief Allows to build a visitor from lambdas to use with std::visit.
   **
   ** This allows to use a syntax such as
   ** std::visit(
   **   LambdaVisitor{
   **     Lambda1,
   **     Lambda2,
   **     ...
   **   }, variant);
   ** to a call specific lambdas depending on the static type of the variant.
   **
   ** For instance, the following code:
   **
   ** std::visit(
   **   LambdaVisitor{
   **     [](int) { std::cout << "It's an int!\n"; },
   **     [](std::string) { std::cout << "It's a string!\n"; },
   **     [](auto) { std::cout << "It's anything else!\n"; },
   **   }, var);
   **
   ** would have the following results for these variants:
   ** std::variant<int, std::string, char> v1 = 1; // It's an int!
   ** std::variant<int, std::string, char> v2 = "Tigrou"; // It's a string!
   ** std::variant<int, std::string, char> v3 = 'a'; // It's anything else!
   **
   ** This allows to perform quick and efficient pattern matching on variants'
   ** static type.
   **
   ** The really powerful thing here is that this can be used to match multiple
   ** variants. For instance the following code:
   **
   ** std::visit(
   **   LambdaVisitor{
   **     [](int, std::string) { ... },
   **     [](auto, std::string) { ... },
   **     [](auto, auto) { ... },
   **   }, var1, var2);
   **
   ** would call the first lambda if var1 is an int and var2 a string, the
   ** second lambda if var2 is a string and var1 anything else than an int,
   ** and the third in any other case.
   **
   ** Do note that you can have a return value for your lambdas, and have
   ** something like so:
   ** int a = std::visit(
   **   LambdaVisitor{
   **     ...
   **   }, var);
   **
   **
   ** Be careful , you must necessarily have a matching lambda for any possible
   ** values of the variants used as arguments! You won't be able to compile
   ** otherwise.
   **/
  template <class... Ts> struct LambdaVisitor : Ts...
  {
    /** C++ actually desugars lambdas to some kind of struct functors.
     ** For instance, the following lambda could be desugared to the following
     ** struct:
     **
     ** auto f = [](int a) { std::cout << a; }
     **
     ** struct {
     **   auto operator()(int a) {
     **     std::cout << a;
     **   }
     ** } f;
     **
     ** We therefore want to access the operator() of every lambda/functor used
     ** to create the LambdaVisitor.
     **/
    using Ts::operator()...;
  };

  /// Class template argument deduction. This allows to implicitly deduce the
  /// templated type of the visitor created from the types of the arguments
  /// it is constructed with, without having to explicitly fill the template.
  template <class... Ts> LambdaVisitor(Ts...) -> LambdaVisitor<Ts...>;

} // namespace misc
