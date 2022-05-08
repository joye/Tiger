/**
 ** \file ast/dumper-dot.cc
 ** \brief Implementation of ast::DumperDot.
 */

#include <ast/all.hh>
#include <ast/dumper-dot.hh>
#include <misc/indent.hh>
#include <misc/symbol.hh>

namespace ast
{
  using namespace ast;

  DumperDot::DumperDot(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void DumperDot::operator()(const ArrayExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "ArrayExp");
    // FIXME: Some code was deleted here (node_html_ports with properties).
    footer_and_link(old_parent_id);
    // FIXME: Some code was deleted here (dump).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const ArrayTy& e)
  {
    unsigned long old_parent_id = node_html_header(e, "ArrayTy");
    node_html_ports({"base_type"});
    footer_and_link(old_parent_id);
    dump("base_type", e.base_type_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const AssignExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "AssignExp");
    // FIXME: Some code was deleted here (node_html_ports with properties).
    footer_and_link(old_parent_id);
    // FIXME: Some code was deleted here (dump).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const BreakExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "BreakExp");
    node_html_ports({"def"});
    footer_and_link(old_parent_id);
    dump_def(e);
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const CallExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "CallExp");
    // FIXME: Some code was deleted here (node_html_field).
    node_html_ports();
    // FIXME: Some code was deleted here (node_html_port_list for each list).
    node_html_one_port("def");
    footer_and_link(old_parent_id);
    dump_def(e);
    // FIXME: Some code was deleted here (dump_list).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const CastExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "CastExp");
    node_html_ports({"exp", "ty"});
    footer_and_link(old_parent_id);
    dump("exp", e.exp_get());
    dump("ty", e.ty_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const ClassTy& e)
  {
    unsigned long old_parent_id = node_html_header(e, "ClassTy");
    node_html_ports({"super", "chunks"});
    footer_and_link(old_parent_id);
    dump("super", e.super_get());
    dump("chunks", e.chunks_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const Field& e)
  {
    unsigned long old_parent_id = node_html_header(e, "Field");
    node_html_field("name", e.name_get());
    node_html_ports({"type_name"});
    footer_and_link(old_parent_id);
    dump("type_name", e.type_name_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const FieldInit& e)
  {
    unsigned long old_parent_id = node_html_header(e, "FieldInit");
    node_html_field("name", e.name_get());
    node_html_ports({"init"});
    footer_and_link(old_parent_id);
    dump("init", e.init_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const FieldVar& e)
  {
    unsigned long old_parent_id = node_html_header(e, "FieldVar");
    // FIXME: Some code was deleted here (node_html_field).
    // FIXME: Some code was deleted here (node_html_ports with properties).
    footer_and_link(old_parent_id);
    // FIXME: Some code was deleted here (dump).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const ForExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "ForExp");
    node_html_ports({"vardec", "hi", "body"});
    footer_and_link(old_parent_id);
    dump("vardec", e.vardec_get());
    dump("hi", e.hi_get());
    dump("body", e.body_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const FunctionDec& e)
  {
    unsigned long old_parent_id = node_html_header(e, "FunctionDec");
    node_html_field("name", e.name_get());
    node_html_ports({"formals", "result", "body"});
    footer_and_link(old_parent_id);
    dump("formals", e.formals_get());
    dump("result", e.result_get());
    dump("body", e.body_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const IfExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "IfExp");
    // FIXME: Some code was deleted here (node_html_ports with properties).
    footer_and_link(old_parent_id);
    // FIXME: Some code was deleted here (dump).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const IntExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "IntExp");
    node_html_field("value", e.value_get());
    footer_and_link(old_parent_id);
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const LetExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "LetExp");
    // FIXME: Some code was deleted here (node_html_ports with properties).
    footer_and_link(old_parent_id);
    // FIXME: Some code was deleted here (dump).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const MethodCallExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "MethodCallExp");
    // FIXME: Some code was deleted here (node_html_field).
    // FIXME: Some code was deleted here (node_html_ports with properties).
    // FIXME: Some code was deleted here (node_html_port_list for each list).
    node_html_one_port("def");
    footer_and_link(old_parent_id);
    dump_def(e);
    // FIXME: Some code was deleted here (dump and dump_list).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const MethodDec& e)
  {
    unsigned long old_parent_id = node_html_header(e, "MethodDec");
    node_html_field("name", e.name_get());
    node_html_ports({"formals", "result", "body"});
    footer_and_link(old_parent_id);
    dump("formals", e.formals_get());
    dump("result", e.result_get());
    dump("body", e.body_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const NameTy& e)
  {
    unsigned long old_parent_id = node_html_header(e, "NameTy");
    node_html_field("name", e.name_get());
    node_html_ports({"def"});
    footer_and_link(old_parent_id);
    dump_def(e);
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const NilExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "NilExp");
    footer_and_link(old_parent_id);
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const ObjectExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "ObjectExp");
    // FIXME: Some code was deleted here (node_html_ports with properties).
    footer_and_link(old_parent_id);
    // FIXME: Some code was deleted here (dump).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const OpExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "OpExp");
    node_html_field("oper", str(e.oper_get()), "'");
    node_html_ports({"left", "right"});
    footer_and_link(old_parent_id);
    dump("left", e.left_get());
    dump("right", e.right_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const RecordExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "RecordExp");
    // FIXME: Some code was deleted here (node_html_ports with properties).
    // FIXME: Some code was deleted here (node_html_port_list for each list).
    footer_and_link(old_parent_id);
    // FIXME: Some code was deleted here (dump and dump_list).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const RecordTy& e)
  {
    unsigned long old_parent_id = node_html_header(e, "RecordTy");
    node_html_ports();
    // FIXME: Some code was deleted here (node_html_port_list for each list).
    footer_and_link(old_parent_id);
    // FIXME: Some code was deleted here (dump_list).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const SeqExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "SeqExp");
    node_html_ports();
    // FIXME: Some code was deleted here (node_html_port_list for each list).
    footer_and_link(old_parent_id);
    // FIXME: Some code was deleted here (dump_list).
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const SimpleVar& e)
  {
    unsigned long old_parent_id = node_html_header(e, "SimpleVar");
    node_html_field("name", e.name_get());
    node_html_ports({"def"});
    footer_and_link(old_parent_id);
    dump_def(e);
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const StringExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "StringExp");
    // FIXME: Some code was deleted here (node_html_field, use misc::escape).
    footer_and_link(old_parent_id);
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const SubscriptVar& e)
  {
    unsigned long old_parent_id = node_html_header(e, "SubscriptVar");
    node_html_ports({"var", "index"});
    footer_and_link(old_parent_id);
    dump("var", e.var_get());
    dump("index", e.index_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const TypeDec& e)
  {
    unsigned long old_parent_id = node_html_header(e, "TypeDec");
    node_html_field("name", e.name_get());
    node_html_ports({"ty"});
    footer_and_link(old_parent_id);
    dump("ty", e.ty_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const VarDec& e)
  {
    unsigned long old_parent_id = node_html_header(e, "VarDec");
    node_html_field("name", e.name_get());
    node_html_ports({"type_name", "init"});
    footer_and_link(old_parent_id);
    dump("type_name", e.type_name_get());
    dump("init", e.init_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const WhileExp& e)
  {
    unsigned long old_parent_id = node_html_header(e, "WhileExp");
    node_html_ports({"test", "body"});
    footer_and_link(old_parent_id);
    dump("test", e.test_get());
    dump("body", e.body_get());
    parent_id = old_parent_id;
  }

  void DumperDot::operator()(const ast::ChunkList& e)
  {
    dump_chunk<ast::ChunkList>(e, "ChunkList");
  }

  void DumperDot::operator()(const ast::FunctionChunk& e)
  {
    dump_chunk<ast::FunctionChunk>(e, "FunctionChunk");
  }

  void DumperDot::operator()(const ast::MethodChunk& e)
  {
    dump_chunk<ast::MethodChunk>(e, "MethodChunk");
  }

  void DumperDot::operator()(const ast::TypeChunk& e)
  {
    dump_chunk<ast::TypeChunk>(e, "TypeChunk");
  }

  void DumperDot::operator()(const ast::VarChunk& e)
  {
    dump_chunk<ast::VarChunk>(e, "VarChunk");
  }
} // namespace ast
