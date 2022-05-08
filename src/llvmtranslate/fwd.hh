#pragma once

#include <map>

#include <ast/fwd.hh>
#include <misc/set.hh>
#include <type/fwd.hh>

namespace llvm
{
  // From llvm/IR/Module.h.
  class Module;

  // From llvm/IR/DerivedTypes.h
  class StructType;

  // From llvm/IR/Type.h
  class Type;

  // From llvm/IR/LLVMContext.h
  class LLVMContext;

} // namespace llvm

namespace llvmtranslate
{
  using escaped_map_type =
    std::map<const type::Function*, misc::set<const ast::VarDec*>>;
  using frame_map_type = escaped_map_type;

} // namespace llvmtranslate
