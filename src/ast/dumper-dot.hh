/**
 ** \file ast/dumper-dot.hh
 ** \brief Declaration of ast::DumperDot.
 */

#pragma once

#include <ast/default-visitor.hh>
#include <misc/escape.hh>

namespace ast
{
  /// \brief Dump an Ast into dot format.
  class DumperDot : public ast::DefaultConstVisitor
  {
  public:
    using super_type = ast::DefaultConstVisitor;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a DumperDot.
    DumperDot(std::ostream& ostr);

    /// Destroy a DumperDot.
    ~DumperDot() override = default;

    // Visit methods.
  public:
    void operator()(const ast::ArrayExp&) override;
    void operator()(const ast::ArrayTy&) override;
    void operator()(const ast::AssignExp&) override;
    void operator()(const ast::BreakExp&) override;
    void operator()(const ast::CallExp&) override;
    void operator()(const ast::CastExp&) override;
    void operator()(const ast::ChunkList&) override;
    void operator()(const ast::ClassTy&) override;
    void operator()(const ast::Field&) override;
    void operator()(const ast::FieldInit&) override;
    void operator()(const ast::FieldVar&) override;
    void operator()(const ast::ForExp&) override;
    void operator()(const ast::FunctionDec&) override;
    void operator()(const ast::IfExp&) override;
    void operator()(const ast::IntExp&) override;
    void operator()(const ast::LetExp&) override;
    void operator()(const ast::MethodCallExp&) override;
    void operator()(const ast::MethodDec&) override;
    void operator()(const ast::NameTy&) override;
    void operator()(const ast::NilExp&) override;
    void operator()(const ast::ObjectExp&) override;
    void operator()(const ast::OpExp&) override;
    void operator()(const ast::RecordExp&) override;
    void operator()(const ast::RecordTy&) override;
    void operator()(const ast::SeqExp&) override;
    void operator()(const ast::SimpleVar&) override;
    void operator()(const ast::StringExp&) override;
    void operator()(const ast::SubscriptVar&) override;
    void operator()(const ast::TypeDec&) override;
    void operator()(const ast::VarDec&) override;
    void operator()(const ast::WhileExp&) override;
    void operator()(const ast::FunctionChunk&) override;
    void operator()(const ast::MethodChunk&) override;
    void operator()(const ast::TypeChunk&) override;
    void operator()(const ast::VarChunk&) override;

  protected:
    template <typename T> void dump(const std::string& field, const T& t);
    template <typename T> void dump(const std::string& field, const T* t);
    template <typename T> void dump_list(const std::string& field, const T& e);
    template <typename T> void dump_def(const T& e) const;
    template <typename E> void dump_chunk(const E& e, const std::string& name);

    void display_link(unsigned long old_parent_id) const;
    void footer_and_link(unsigned long old_parent_id) const;

    template <typename T>
    unsigned long node_html_header(const T& e, const std::string& type);
    template <typename T>
    void node_html_field(const std::string& name,
                         const T& content,
                         const std::string& sep = "");
    void node_html_one_port(const std::string& p);
    void node_html_ports(const std::vector<std::string>& ports = {});
    template <typename T>
    void node_html_port_list(const std::string& name,
                             const T& list,
                             bool chunk = false);
    void node_html_footer() const;

  protected:
    /// The stream to print on.
    std::ostream& ostr_;

    /// The parent id
    unsigned long parent_id = -1;

    /// Number of fields
    unsigned long inner_fields = 0;

    /// The parent field
    const std::string* parent_field = nullptr;
  };

} // namespace ast

#include <ast/dumper-dot.hxx>
