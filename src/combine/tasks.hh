/**
 ** \file combine/tasks.hh
 ** \brief Combine module related tasks.
 */

#pragma once

#include <overload/binder.hh>
#include <task/libtask.hh>

namespace combine::tasks
{
  TASK_GROUP("Combine");

  BOOLEAN_TASK_DECLARE("c-object", "combine objects", c_object_p, "object");
  BOOLEAN_TASK_DECLARE("c-bounds", "combine bounds checking", c_bounds_p, "");
  BOOLEAN_TASK_DECLARE("c-escapes", "combine escapes", c_escapes_p, "");
  BOOLEAN_TASK_DECLARE("c-desugar",
                       "combine for and string comparison desugaring",
                       c_desugar_p,
                       "desugar-for desugar-string-cmp");
  BOOLEAN_TASK_DECLARE("c-inline", "combine inlining", c_inline_p, "");
  BOOLEAN_TASK_DECLARE("c-prune", "combine pruning", c_prune_p, "");
  BOOLEAN_TASK_DECLARE("c-overload", "combine overloading", c_overload_p, "");

  BOOLEAN_TASK_DECLARE(
    "a|c-all",
    "combine all compiler options",
    c_all_p,
    "c-object c-bounds c-escapes c-desugar c-inline c-prune c-overload");

  TASK_DECLARE("combine-bindings-compute",
               "bind the identifiers, "
               "allowing various compiler options",
               combine_bindings_compute,
               "parse");

  TASK_DECLARE("combine-types-compute",
               "check for type violations, "
               "allowing various compiler options",
               combine_types_compute,
               "combine-bindings-compute");

  TASK_DECLARE("combine-rename",
               "rename identifiers to unique names, "
               "allowing various compiler options",
               combine_rename,
               "combine-types-compute");

  TASK_DECLARE("c|combine-desugar",
               "remove object and complex constructs from the program"
               "allowing various compiler options",
               combine_desugar,
               "combine-rename");

} // namespace combine::tasks
