/**
 ** \file inlining/pruner.cc
 ** \brief Implementation of inlining::Pruner.
 */

#include <inlining/pruner.hh>
#include <range/v3/algorithm/remove_if.hpp>

namespace inlining
{
  using namespace ast;

  ast::FunctionChunk* Pruner::prune(ast::FunctionChunk& e)
  {
    while (true)
      {
        auto it = ranges::remove_if(e, [&](ast::FunctionDec* func_dec) {
          if (!func_dec->body_get() || func_dec->name_get() == "_main")
            return false;
          else
            return called_functions_[func_dec->name_get()] == 0;
        });

        if (it == e.end())
          break;
        e.erase(it, e.end());
      }

    return new FunctionChunk(e.location_get(), &e.decs_get());
  }

  // FIXME: Some code was deleted here.

} // namespace inlining
