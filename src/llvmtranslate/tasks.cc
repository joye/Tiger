/**
 ** \file llvmtranslate/tasks.cc
 ** \brief LLVM Translate tasks.
 */

#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <llvm/Config/llvm-config.h> // LLVM_VERSION_*
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Support/raw_ostream.h> // llvm::outs()

#pragma GCC diagnostic pop

#include <ast/tasks.hh>
#include <llvmtranslate/fwd.hh>
#include <llvmtranslate/libllvmtranslate.hh>
#define DEFINE_TASKS 1
#include <llvmtranslate/tasks.hh>
#undef DEFINE_TASKS

namespace llvmtranslate::tasks
{
  std::pair<std::unique_ptr<llvm::LLVMContext>, std::unique_ptr<llvm::Module>>
    module = {nullptr, nullptr};

  /// Translate the AST to LLVM IR.
  void llvm_compute() { module = translate(*ast::tasks::the_program); }

  /// Display the LLVM IR.
  void llvm_display()
  {
    // If the runtime has to be displayed, get the runtime module,
    // link it with the program module and print it.
    if (llvm_runtime_display_p)
      {
        auto runtime = runtime_get(*module.first);
#if LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR <= 7
        auto link =
          llvm::Linker::LinkModules(module.second.get(), runtime.get());
#else
        auto link =
          llvm::Linker::linkModules(*module.second, std::move(runtime));
#endif
        (void)link;
        postcondition(!link); // Returns true on error
      }

    auto& out = llvm::outs();
    llvm::PrintModulePass printer{out};
#if LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR <= 8
    printer.run(*module.second);
#else
    llvm::ModuleAnalysisManager dummy_mam;
    printer.run(*module.second, dummy_mam);
#endif
  }

} // namespace llvmtranslate::tasks
