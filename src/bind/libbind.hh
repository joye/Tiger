/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
 */

#include <misc/error.hh>

// DONE: Some code was deleted here.
namespace bind
{
  misc::error bind(ast::Ast& tree);
  void rename(ast::Ast& tree);
} // namespace bind