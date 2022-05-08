/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

#include <task/libtask.hh>

// DONE: Some code was deleted here.
namespace bind
{
  namespace tasks
  {
    TASK_GROUP("3. Binding");

    TASK_DECLARE("bound", "Are bindings computed ?.",
                 bound, "bindings-compute");

    TASK_DECLARE("b|bindings-compute",
                 "Bind to the king.",
                 bind, "parse");

    TASK_DECLARE("B|bindings-display",
                 "Enable the bindings display.",
                 bind_display, "");
    TASK_DECLARE("rename", "Display all renamable nodes (Var/Func).", rename, "bindings-compute");
  }
}