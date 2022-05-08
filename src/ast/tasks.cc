/**
 ** \file ast/tasks.cc
 ** \brief Ast Tasks implementation.
 */

#include <ast/libast.hh>
#include <misc/contract.hh>
#define DEFINE_TASKS 1
#include <ast/tasks.hh>
#undef DEFINE_TASKS

namespace ast::tasks
{
  // The abstract syntax tree.
  std::unique_ptr<ast::ChunkList> the_program(nullptr);

  void ast_display()
  {
    precondition(the_program);
    // MODIFIED?
    std::cout << "/* == Abstract Syntax Tree. == */\n\n"
              << *the_program << std::endl;
  }

  void ast_dump()
  {
    precondition(the_program);
    ast::dump_dot(*the_program, std::cout);
  }

} // namespace ast::tasks
