/**
 ** \file parse/tiger-driver.hh
 ** \brief Declaration of parse::TigerDriver.
 */

#pragma once

#include <ast/all.hh>
#include <ast/fwd.hh>
#include <parse/location.hh>

namespace parse
{
  class TigerDriver
  {
  public:
    TigerDriver() = default;
    ~TigerDriver() = default;

    ast::IntExp* make_IntExp(const location& location, int num) const;

    ast::StringExp* make_StringExp(const location& location,
                                   std::string string) const;

    ast::ObjectExp* make_ObjectExp(const location& location,
                                   ast::NameTy* type_name) const;

    ast::CallExp* make_CallExp(const location& location,
                               misc::symbol name,
                               ast::exps_type* args) const;

    ast::MethodCallExp* make_MethodCallExp(const location& location,
                                           misc::symbol name,
                                           ast::exps_type* args,
                                           ast::Var* object) const;

    ast::RecordExp* make_RecordExp(const location& location,
                                   ast::NameTy* type_name,
                                   ast::fieldinits_type* fields) const;

    ast::ArrayExp* make_ArrayExp(const location& location,
                                 ast::NameTy* type_name,
                                 ast::Exp* size,
                                 ast::Exp* init) const;

    ast::NilExp* make_NilExp(const location& location) const;

    ast::SeqExp* make_SeqExp(const location& location,
                             ast::exps_type* exps) const;

    ast::AssignExp* make_AssignExp(const location& location,
                                   ast::Var* var,
                                   ast::Exp* exp) const;

    ast::IfExp* make_IfExp(const location& location,
                           ast::Exp* test,
                           ast::Exp* thenclause,
                           ast::Exp* elseclause) const;

    ast::IfExp* make_IfExp(const location& location,
                           ast::Exp* test,
                           ast::Exp* thenclause) const;

    ast::WhileExp* make_WhileExp(const location& location,
                                 ast::Exp* test,
                                 ast::Exp* body) const;

    ast::ForExp* make_ForExp(const location& location,
                             ast::VarDec* vardec,
                             ast::Exp* hi,
                             ast::Exp* body) const;

    ast::BreakExp* make_BreakExp(const location& location) const;

    ast::LetExp* make_LetExp(const location& location,
                             ast::ChunkList* decs,
                             ast::Exp* body) const;

    ast::OpExp* make_OpExp(const location& location,
                           ast::Exp* left,
                           ast::OpExp::Oper oper,
                           ast::Exp* right) const;

    ast::CastExp*
    make_CastExp(const location& location, ast::Exp* exp, ast::Ty* ty) const;

    ast::SimpleVar* make_SimpleVar(const location& location,
                                   misc::symbol name) const;

    ast::FieldVar* make_FieldVar(const location& location,
                                 ast::Var* var,
                                 misc::symbol name) const;

    ast::SubscriptVar* make_SubscriptVar(const location& location,
                                         ast::Var* var,
                                         ast::Exp* index) const;

    /* Use expansion parameter pack to handle when we have one or empty arguments */
    template <class... T> ast::exps_type* make_exps_type(T... exps) const;

    ast::ChunkList* make_ChunkList(const location& location) const;

    ast::TypeChunk* make_TypeChunk(const location& location) const;

    ast::TypeDec*
    make_TypeDec(const location& location, misc::symbol name, ast::Ty* ty);

    ast::RecordTy* make_RecordTy(const location& location,
                                 ast::fields_type* fields);

    ast::ArrayTy* make_ArrayTy(const location& location,
                               ast::NameTy* base_type) const;

    template <class... T> ast::fields_type* make_fields_type(T... types) const;

    ast::Field* make_Field(const location& location,
                           misc::symbol name,
                           ast::NameTy* type_name) const;

    ast::NameTy* make_NameTy(const location& location, misc::symbol name) const;

    template <class... T>
    ast::fieldinits_type* make_fieldinits_type(T... inits_types) const;

    ast::FieldInit* make_FieldInit(const location& location,
                                   misc::symbol name,
                                   ast::Exp* init) const;

    ast::ClassTy* make_ClassTy(const location& location,
                               ast::NameTy* super,
                               ast::ChunkList* decs) const;

    ast::VarChunk* make_VarChunk(const location& location) const;

    ast::VarDec* make_VarDec(const location& location,
                             misc::symbol name,
                             ast::NameTy* type_name,
                             ast::Exp* init) const;

    ast::MethodChunk* make_MethodChunk(const location& location) const;

    ast::MethodDec* make_MethodDec(const location& location,
                                   misc::symbol name,
                                   ast::VarChunk* formals,
                                   ast::NameTy* result,
                                   ast::Exp* body) const;

    ast::FunctionDec* make_FunctionDec(const location& location,
                                       misc::symbol name,
                                       ast::VarChunk* formals,
                                       ast::NameTy* result,
                                       ast::Exp* body) const;

    ast::VarChunk* field_to_dec(const location& location, std::vector<ast::Field*>* a) const;

    template <class... T> ast::FunctionChunk* make_FunctionChunk(T... args);
  };
} // namespace parse

#include <parse/tiger-driver.hxx>
