#pragma once

#include <llvmtranslate/fwd.hh>
#include <task/libtask.hh>

namespace llvmtranslate::tasks
{
  /// The global translation module of ast;:tasks::the_program.
  extern std::pair<std::unique_ptr<llvm::LLVMContext>,
                   std::unique_ptr<llvm::Module>>
    module;

  TASK_GROUP("5.5. Translation to LLVM Intermediate Representation");

  /// Translate the AST to LLVM IR.
  TASK_DECLARE("llvm-compute",
               "translate to LLVM IR",
               llvm_compute,
               "typed desugar-for desugar-string-cmp desugar");

  /// Activate displaying the runtime along with the LLVM IR.
  BOOLEAN_TASK_DECLARE("llvm-runtime-display",
                       "enable runtime displaying"
                       "along with the LLVM IR",
                       llvm_runtime_display_p,
                       "");

  /// Display the LLVM IR.
  TASK_DECLARE("llvm-display",
               "display the LLVM IR",
               llvm_display,
               "llvm-compute");

} // namespace llvmtranslate::tasks
