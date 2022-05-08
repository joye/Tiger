/**
 ** \file llvmtranslate/translator.hh
 ** \brief Declaration of llvmtranslate::Translator
 */

#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#pragma GCC diagnostic pop

#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>
#include <llvmtranslate/fwd.hh>
#include <llvmtranslate/llvm-type-visitor.hh>

namespace llvmtranslate
{
  class Translator
    : public ast::DefaultConstVisitor
    , public ast::NonObjectConstVisitor
  {
  public:
    /// Super class.
    using super_type = ast::DefaultConstVisitor;
    /// Import overloaded operator() methods.
    using super_type::operator();

    Translator(llvm::Module& module, escaped_map_type&& escaped);

    /// Run the translation.
    void operator()(const ast::Ast& e) override;

    /// \brief Run this visitor on \a node, and return its translation.
    ///
    /// It is also guaranteed that \a value_ is set to it.
    /// More generally, this routine saves from direct calls to \a accept.
    llvm::Value* translate(const ast::Ast& node);

    /// \name Lvalues
    /// \{
    void operator()(const ast::SimpleVar& e) override;
    void operator()(const ast::FieldVar& e) override;
    void operator()(const ast::SubscriptVar& e) override;
    /// \}

    /// \name Expressions
    /// \{
    void operator()(const ast::NilExp&) override;
    void operator()(const ast::IntExp& e) override;
    void operator()(const ast::StringExp& e) override;
    void operator()(const ast::RecordExp& e) override;
    void operator()(const ast::CallExp& e) override;
    void operator()(const ast::OpExp& e) override;
    void operator()(const ast::SeqExp& e) override;
    void operator()(const ast::AssignExp& e) override;
    void operator()(const ast::IfExp& e) override;
    void operator()(const ast::WhileExp& e) override;
    void operator()(const ast::BreakExp&) override;
    void operator()(const ast::ArrayExp& e) override;
    void operator()(const ast::CastExp& e) override;
    /// \}

    /// \name Declarations
    /// \{
    void operator()(const ast::FunctionChunk& e) override;
    void visit_function_dec_header(const ast::FunctionDec& e);
    void visit_function_dec_body(const ast::FunctionDec& e);
    void operator()(const ast::VarDec& e) override;
    /// \}

  protected:
    /// The translation of the last visited node.
    llvm::Value* value_ = nullptr;

    /// The current function.
    llvm::Function* current_function_ = nullptr;

    /// The module containing the metadata and this file's AST.
    llvm::Module& module_;

    /// The global context of the translator.
    llvm::LLVMContext& ctx_;

    /// IR builder to simplify building nodes and instructions.
    llvm::IRBuilder<> builder_;

    /// Access for each "variable".
    /// Since the AST doesn't contain the arguments added
    /// for the lambda lifting, we need to identify them by their declaration.
    std::map<const llvm::Function*, std::map<const ast::VarDec*, llvm::Value*>>
      locals_;

    /// For each loop, the basic block immediately after it.
    std::map<const ast::WhileExp*, llvm::BasicBlock*> loop_end_;

    /// Access every escaped variable for each function.
    escaped_map_type escaped_;

    /// The llvm type translator.
    LLVMTypeVisitor type_visitor_;

  private:
    /// Get a LLVM access to a variable, usually to be loaded right after.
    llvm::Value* access_var(const ast::Var& e);

    /// Call the init_array function that allocates and initialize the array.
    llvm::Value* init_array(llvm::Value* count_val, llvm::Value* init_val);

    /// Get a llvm::Type from a type::Type using the type_visitor_.
    llvm::Type* llvm_type(const type::Type& type);

    /// Create a llvm function from a function type.
    llvm::FunctionType* llvm_function_type(const type::Function& function_t);
  };

} // namespace llvmtranslate

#include <llvmtranslate/translator.hxx>
