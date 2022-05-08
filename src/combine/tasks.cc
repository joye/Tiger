/**
 ** \file combine/tasks.cc
 ** \brief Combine module related tasks' implementation.
 */

#include <ast/tasks.hh>
#include <bind/tasks.hh>
#include <desugar/tasks.hh>
#include <escapes/tasks.hh>
#include <object/tasks.hh>

#include <astclone/libastclone.hh>
#include <desugar/libdesugar.hh>
#include <inlining/libinlining.hh>

#include <common.hh>

#include <combine/libcombine.hh>
#define DEFINE_TASKS 1
#include <combine/tasks.hh>
#undef DEFINE_TASKS

namespace combine::tasks
{
  std::unique_ptr<overload::overfun_bindings_type> the_overfun_bindings =
    nullptr;

  void combine_bindings_compute()
  {
    auto result =
      ::combine::combine_bind(*ast::tasks::the_program, c_overload_p);
    ::combine::tasks::the_overfun_bindings =
      std::make_unique<overload::overfun_bindings_type>(
        std::move(result.first));

    task_error() << result.second << &misc::error::exit_on_error;
  }

  void combine_types_compute()
  {
    task_error() << ::combine::combine_types_check(
      *ast::tasks::the_program, *::combine::tasks::the_overfun_bindings,
      c_overload_p);
    the_overfun_bindings.reset();
    task_error().exit_on_error();
  }

  void combine_rename()
  {
    // FIXME: Some code was deleted here (Call appropriate renaming tasks).
  }

  void combine_desugar()
  {
    if (c_object_p)
      ::object::tasks::object_desugar();

    if (c_desugar_p)
      ::desugar::tasks::desugar();

    if (c_bounds_p)
      astclone::apply(::desugar::bounds_checks_add, ast::tasks::the_program);

    if (c_inline_p)
      astclone::apply(::inlining::inline_expand, ast::tasks::the_program);

    if (c_prune_p)
      astclone::apply(::inlining::prune, ast::tasks::the_program);

    if (c_escapes_p)
      ::escapes::tasks::escapes_compute();
  }

} // namespace combine::tasks
