/**
 ** \file llvmtranslate/llvm-type-visitor.hh
 ** \brief Definition of llvmtranslator::LLVMTypeVisitor.
 */

#pragma once

#include <llvm/IR/LLVMContext.h>

#include <llvmtranslate/fwd.hh>
#include <type/default-visitor.hh>

namespace llvmtranslate
{
  /// Visit a Type and return the corresponding llvm::Type.
  class LLVMTypeVisitor : public type::DefaultConstVisitor
  {
  public:
    using super_type = type::DefaultConstVisitor;
    // Import overloaded virtual functions.
    using super_type::operator();

    LLVMTypeVisitor(llvm::LLVMContext& ctx);

    llvm::Type* llvm_type_get();

    /// Visit methods.
    /// \{
    void operator()(const type::Nil& e) override;
    void operator()(const type::Void& e) override;
    void operator()(const type::Int& e) override;
    void operator()(const type::String& e) override;
    void operator()(const type::Named& e) override;
    void operator()(const type::Record& e) override;
    void operator()(const type::Array& e) override;
    /// \}

  private:
    /// The global context.
    llvm::LLVMContext& ctx_;
    /// The type of the last visited node.
    llvm::Type* type_ = nullptr;
    /// llvm::StructTypes for each type::Record
    std::map<const type::Record*, llvm::StructType*> structs_;
    /// Recurse and return the type_.
    llvm::Type* llvm_type(const type::Type& type);
  };

} // namespace llvmtranslate
