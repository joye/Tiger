/**
 ** \file desugar/desugar-visitor.cc
 ** \brief Implementation of desugar::DesugarVisitor.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <desugar/desugar-visitor.hh>
#include <misc/algorithm.hh>
#include <misc/symbol.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>

namespace desugar
{
  DesugarVisitor::DesugarVisitor(bool desugar_for_p, bool desugar_string_cmp_p)
    : super_type()
    , desugar_for_p_(desugar_for_p)
    , desugar_string_cmp_p_(desugar_string_cmp_p)
  {}

  /*-----------------------------.
  | Desugar string comparisons.  |
  `-----------------------------*/
  void DesugarVisitor::operator()(const ast::OpExp& e)
  {
    // FIXME: Some code was deleted here.
    const auto location = e.location_get();
    auto left = dynamic_cast<ast::StringExp*>(recurse(e.left_get()));
    auto right = dynamic_cast<ast::StringExp*>(recurse(e.right_get()));
    if (!left || !right)
      {
        const ast::Location& location = e.location_get();
        ast::Exp* left = recurse(e.left_get());
        ast::OpExp::Oper oper = e.oper_get();
        ast::Exp* right = recurse(e.right_get());
        result_ = new ast::OpExp(location, left, oper, right);
        return;
      }
    misc::symbol _func;
    if (e.oper_get() == ast::OpExp::Oper::add)
      {
        result_ =
          new ast::StringExp{location, left->value_get() + right->value_get()};
      }
    else if (e.oper_get() == ast::OpExp::Oper::eq)
      {
        _func = misc::symbol("streq");
        result_ =
          new ast::CallExp{location, _func, new ast::exps_type{left, right}};
      }
    else if (e.oper_get() == ast::OpExp::Oper::ne)
      {
        _func = misc::symbol("streq");
        auto callexp =
          new ast::CallExp{location, _func, new ast::exps_type{left, right}};
        result_ = new ast::OpExp(location, callexp, ast::OpExp::Oper::eq,
                                 new ast::IntExp(location, 0));
      }
    else if (e.oper_get() <= ast::OpExp::Oper::div)
      {
        misc::error er;
        er << "Unimplemented operator: " << str(e.oper_get())
           << misc::error::error_type::failure << std::endl;
      }
    else
      {
        _func = misc::symbol("strcmp");
        auto callexp =
          new ast::CallExp{location, _func, new ast::exps_type{left, right}};
        result_ = new ast::OpExp(location, callexp, e.oper_get(),
                                 new ast::IntExp(location, 0));
      }
  }

  /*----------------------.
  | Desugar `for' loops.  |
  `----------------------*/

  /*<<-
    Desugar `for' loops as `while' loops:

       for i := lo to hi do
         body

     is transformed as:

       let
         var _lo := lo
         var _hi := hi
         var i := _lo
       in
         if i <= _hi then
           while 1 do
             (
               body;
               if i = _hi then
                 break;
               i := i + 1
             )
       end

     Notice that:

     - a `_hi' variable is introduced so that `hi' is evaluated only
       once;

     - a `_lo' variable is introduced to prevent `i' from being in the
       scope of `_hi';

     - a first test is performed before entering the loop, so that the
       loop condition becomes `i < _hi' (instead of `i <= _hi'); this
       is done to prevent overflows on INT_MAX.
       ->>*/

  void DesugarVisitor::operator()(const ast::ForExp& e)
  {
    // FIXME: Some code was deleted here.
    // deleted line
    // Var get

    ast::VarDec* lo = recurse(e.vardec_get());
    const ast::Location& location = e.location_get();
    ast::VarDec* vardec = recurse(e.vardec_get());
    ast::Exp* hi = recurse(e.hi_get());
    ast::Exp* body = recurse(e.body_get());

    // Var def
    auto intsymbol = misc::symbol("int");
    ast::VarDec* _lo =
      new ast::VarDec{location, misc::symbol("_lo"),
                      new ast::NameTy{location, intsymbol}, lo->init_get()};
    ast::VarDec* _hi = new ast::VarDec{
      location, misc::symbol("_hi"), new ast::NameTy{location, intsymbol}, hi};
    ast::VarDec* i =
      new ast::VarDec{location, misc::symbol(vardec->name_get().get()),
                      new ast::NameTy{location, intsymbol},
                      new ast::SimpleVar(location, _lo->name_get())};

    // VarChunk
    auto chunkl = new ast::ChunkList(e.location_get());
    auto var_chunk = new ast::VarChunk(location);
    var_chunk->push_front(*i);
    var_chunk->push_front(*_hi);
    var_chunk->push_front(*_lo);
    chunkl->push_front(var_chunk);

    // While

    ast::IntExp* test = new ast::IntExp{location, 1};
    ast::exps_type* exps = new ast::exps_type();
    auto ifexp_while = new ast::IfExp{
      location,
      new ast::OpExp(location, new ast::SimpleVar(location, i->name_get()),
                     ast::OpExp::Oper::eq,
                     new ast::SimpleVar(location, _hi->name_get())),
      new ast::BreakExp(location), nullptr};
    exps->push_back(body);
    exps->push_back(ifexp_while);
    exps->push_back(new ast::AssignExp(
      location, new ast::SimpleVar(location, i->name_get()),
      new ast::OpExp(location, new ast::SimpleVar(location, i->name_get()),
                     ast::OpExp::Oper::add, new ast::IntExp(location, 1))));
    ast::WhileExp* _while =
      new ast::WhileExp{location, test, new ast::SeqExp{location, exps}};

    // IfExp
    auto ifexp = new ast::IfExp{
      location,
      new ast::OpExp(location, new ast::SimpleVar(location, _lo->name_get()),
                     ast::OpExp::Oper::le,
                     new ast::SimpleVar(location, _hi->name_get())),
      _while, nullptr};

    // LetExp
    ast::LetExp* let = new ast::LetExp{location, chunkl, ifexp};
    result_ = let;
  }

} // namespace desugar
