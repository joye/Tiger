/**
 ** \file ast/tasks.hh
 ** \brief Ast module related tasks.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <task/libtask.hh>

namespace ast::tasks
{
  /// Global root node of abstract syntax tree.
  extern std::unique_ptr<ast::ChunkList> the_program;

  TASK_GROUP("2. Abstract Syntax Tree");

  /// Display the abstract syntax tree.
  TASK_DECLARE("A|ast-display", "display the AST", ast_display, "parse");

  /// Display the abstract syntax tree using a dumper.
  TASK_DECLARE("ast-dump", "dump the AST", ast_dump, "parse");

} // namespace ast::tasks
