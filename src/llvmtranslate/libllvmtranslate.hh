/**
 ** \file llvmtranslate/libllvmtranslate.hh
 ** \brief Public llvmtranslate module interface declaration.
 */

#pragma once

#include <memory>
#include <utility>

#include <llvm/IR/LLVMContext.h>

#include <ast/fwd.hh>
#include <llvmtranslate/fwd.hh>

/// Translation from ast::Ast to llvm::Value.
namespace llvmtranslate
{
  /// Translate the file into a llvm::Module.
  std::pair<std::unique_ptr<llvm::LLVMContext>, std::unique_ptr<llvm::Module>>
  translate(const ast::Ast& the_program);

  /// Load the runtime as a llvm::Module.
  std::unique_ptr<llvm::Module> runtime_get(llvm::LLVMContext& ctx);

  /// The LLVM runtime as a string, loaded from the generated file.
  /// This function is implemented in $(build_dir)/src/llvmtranslate/runtime.cc
  /// For more information take a look at `local.am`.
  const char* runtime_string();

} // namespace llvmtranslate
