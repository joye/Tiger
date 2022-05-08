/**
 ** \file combine/libcombine.hh
 ** \brief Declare functions and variables exported by combine module.
 */

#pragma once

#include <ast/fwd.hh>
#include <misc/error.hh>
#include <overload/binder.hh>

namespace combine
{
  /*-------.
  | Bind.  |
  `-------*/

  /** \brief Bind identifier uses to their definition, allowing
      function overloading, and return a list of potential definition
      sites for each function call.

      \param tree AST to bind.

      \return a pair whose first element is the potential function
              bindings, and the second element the error status.  */
  std::pair<overload::overfun_bindings_type, misc::error>
  combine_bind(ast::Ast& tree, bool overloads_enabled);

  /*------------------------------.
  | Compute types with overload.  |
  `------------------------------*/

  /** \brief Check types allowing function overloading.

      \param tree             abstract syntax tree's root.
      \param combine_bindings potential function bindings.

      \return success of the type-checking.  */
  misc::error
  combine_types_check(ast::Ast& tree,
                      const overload::overfun_bindings_type& combine_bindings,
                      bool overloads_enabled);

} // namespace combine
