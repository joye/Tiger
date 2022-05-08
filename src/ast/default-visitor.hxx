/**
 ** \file ast/default-visitor.hxx
 ** \brief Implementation for ast/default-visitor.hh.
 */

#pragma once

#include <ast/all.hh>
#include <ast/default-visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  template <template <typename> class Const>
  GenDefaultVisitor<Const>::GenDefaultVisitor()
    : GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenDefaultVisitor<Const>::~GenDefaultVisitor()
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<Ast>& e)
  {
    super_type::operator()(e);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<SimpleVar>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<FieldVar>& e)
  {
    // DONE: Some code was deleted here
    e.var_get()->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<SubscriptVar>& e)
  {
    e.var_get().accept(*this);
    e.index_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<NilExp>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<IntExp>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<StringExp>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<CallExp>& e)
  {
    // DONE: Some code was deleted here.
    for (auto dec : *e.args_get())
      dec->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<OpExp>& e)
  {
    e.left_get().accept(*this);
    e.right_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<RecordExp>& e)
  {
    // DONE: Some code was deleted here.
    e.get_type_name()->accept(*this);
    for (auto dec : *e.get_fieldinits_type())
      dec->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<SeqExp>& e)
  {
    // DONE: Some code was deleted here.
    for (auto dec : *e.get_exps())
      dec->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<AssignExp>& e)
  {
    // DONE: Some code was deleted here.
    e.get_var()->accept(*this);
    e.get_exp()->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<IfExp>& e)
  {
    // DONE: Some code was deleted here.
    e.get_test()->accept(*this);
    e.get_thenclause()->accept(*this);
    auto v = e.get_elseclause();
    if (v != nullptr)
      v->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<WhileExp>& e)
  {
    e.test_get().accept(*this);
    e.body_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<ForExp>& e)
  {
    e.vardec_get().accept(*this);
    e.hi_get().accept(*this);
    e.body_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<BreakExp>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<LetExp>& e)
  {
    // DONE: Some code was deleted here.
    e.get_body()->accept(*this);
    for (auto dec : e.get_chunkList()->chunks_get())
      dec->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<ArrayExp>& e)
  {
    // DONE: Some code was deleted here.
    e.get_type_name()->accept(*this);
    e.get_size()->accept(*this);
    e.get_init()->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<CastExp>& e)
  {
    e.exp_get().accept(*this);
    e.ty_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<FieldInit>& e)
  {
    e.init_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<ChunkList>& e)
  {
    // DONE: Some code was deleted here.
    for (auto dec : e.chunks_get())
      dec->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<ChunkInterface>& e)
  {
    e.accept(*this);
  }

  template <template <typename> class Const>
  template <typename ChunkType>
  inline void GenDefaultVisitor<Const>::chunk_visit(const_t<ChunkType>& e)
  {
    for (const auto dec : e)
      dec->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<VarChunk>& e)
  {
    chunk_visit<VarChunk>(e);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<VarDec>& e)
  {
    // `type_name' might be omitted.
    this->accept(e.type_name_get());
    // `init' can be null in case of formal parameter.
    this->accept(e.init_get());
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<FunctionChunk>& e)
  {
    chunk_visit<FunctionChunk>(e);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<FunctionDec>& e)
  {
    // DONE: Some code was deleted here.
    if (e.result_get())
      e.result_get()->accept(*this);
    if (e.body_get())
      e.body_get()->accept(*this);
    chunk_visit<VarChunk>(e.formals_get());
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<TypeChunk>& e)
  {
    chunk_visit<TypeChunk>(e);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<TypeDec>& e)
  {
    e.ty_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<NameTy>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<RecordTy>& e)
  {
    // DONE: Some code was deleted here.
    for (auto dec : *e.get_fields())
      dec->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<ArrayTy>& e)
  {
    e.base_type_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<Field>& e)
  {
    e.type_name_get().accept(*this);
  }

} // namespace ast
