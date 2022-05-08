/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */

// DONE: Some code was deleted here.
#include <bind/binder.hh>
#include <bind/libbind.hh>
#include <bind/renamer.hh>

namespace bind
{

  misc::error bind(ast::Ast& tree)
  {
    Binder bc;
    bc(tree);
    return bc.error_get();
  }
  void rename(ast::Ast& tree)
  {
    Renamer rc;
    rc(tree);
  }
}