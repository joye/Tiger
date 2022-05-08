/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>

#include <type/class.hh>

namespace ast
{
  // Anonymous namespace: these functions are private to this file.
  namespace
  {
    /// Output \a e on \a ostr.
    inline std::ostream& operator<<(std::ostream& ostr, const Escapable& e)
    {
      if (escapes_display(ostr)
          // DONE: Some code was deleted here.
      )
        ostr << "/* escaping */ ";

      return ostr;
    }

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      if (bindings_display(ostr))
        ostr << " /* " << &e << " */";
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    // DONE: Some code was deleted here.
    ostr_ << *e.var_get() << '.' << e.name_get();
  }

  /* Foo[10]. */
  void PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
          << misc::decindent << ']';
  }

  void PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get();
    ostr_ << ", " << e.ty_get() << ')';
  }

  // DONE: Some code was deleted here.

  void PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << *e.get_type_name();

    if (bindings_display(ostr_))
      ostr_ << "/* " << e.get_type_name()->def_get() << " */";
    ostr_ << "[";
    ostr_ << *e.get_size();
    ostr_ << "] of ";
    ostr_ << *e.get_init();
  }

  void PrettyPrinter::operator()(const ArrayTy& e)
  {
    ostr_ << "array of ";
    ostr_ << e.base_type_get();
  }

  void PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << "(";
    ostr_ << *e.get_var();
    ostr_ << " := ";
    ostr_ << *e.get_exp();
    ostr_ << ")";
  }

  void PrettyPrinter::operator()(const BreakExp& e)
  {
    if (bindings_display(ostr_))
      {
        ostr_ << "break";
        ostr_ << "/* " << e.loop_get() << " */";
      }
    else
      {
        ostr_ << "break";
      }
  }

  void PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.name_get();

    if (bindings_display(ostr_))
      {
        ostr_ << " /* " << e.def_get() << " */";
        ostr_ << "(";
        for (auto& exp : *e.args_get())
          {
            if (exp == (*e.args_get()).back())
              ostr_ << *exp;
            else
              ostr_ << *exp << ", ";
          }
        ostr_ << ")";
      }
    else
      {
        ostr_ << "(";
        for (auto& exp : *e.args_get())
          {
            if (exp == (*e.args_get()).back())
              ostr_ << *exp;
            else
              ostr_ << *exp << ", ";
          }
        ostr_ << ")";
      }
  }

  void PrettyPrinter::operator()(const VarChunk& e)
  {
    size_t i = 0;
    for (auto* a : e.decs_get())
      {
        if (i++ != 0)
          ostr_ << misc::iendl;
        this->operator()(*a);
      }
  }

  void PrettyPrinter::operator()(const MethodChunk& e)
  {
    size_t i = 0;
    for (auto* a : e.decs_get())
      {
        if (i++ != 0)
          ostr_ << misc::iendl;
        this->operator()(*a);
      }
  }

  void PrettyPrinter::operator()(const TypeChunk& e)
  {
    size_t i = 0;
    for (auto* a : e.decs_get())
      {
        if (i++ != 0)
          ostr_ << misc::iendl;
        this->operator()(*a);
      }
  }

  void PrettyPrinter::operator()(const FunctionChunk& e)
  {
    size_t i = 0;
    for (auto* a : e.decs_get())
      {
        if (i++ != 0)
          ostr_ << misc::iendl;
        this->operator()(*a);
      }
  }

  void PrettyPrinter::operator()(const ClassTy& e)
  {
    ostr_ << misc::iendl << "class ";
    ostr_ << "extends " << e.super_get().name_get();
    size_t i = 0;
    size_t len = 0;
    for (auto& dec : e.chunks_get())
      {
        (void)dec;
        len++;
      }
    if (len > 0)
      {
        ostr_ << misc::iendl << "{" << misc::incendl;

        for (auto a : e.chunks_get().chunks_get())
          {
            ostr_ << *a;
            if (i != len - 1)
              ostr_ << misc::iendl;
            else
              ostr_ << misc::decendl;
            i++;
          }
        ostr_ << "}";
      }
    else
      {
        ostr_ << misc::iendl << "{" << misc::iendl << "}";
      }
  }

  void PrettyPrinter::operator()(const Field& e) { ostr_ << e.name_get(); }

  void PrettyPrinter::operator()(const FieldInit& e)
  {
    ostr_ << e.name_get();
    ostr_ << ": " << e.init_get();
  }

  void PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << "(for ";
    if (bindings_display(ostr_))
      ostr_ << "/* " << &e << " */ ";
    ostr_ << e.vardec_get().name_get();

    if (bindings_display(ostr_))
      ostr_ << " /* " << &e.vardec_get() << " */ ";
    ostr_ << " := " << *e.vardec_get().init_get() << " to " << e.hi_get();
    ostr_ << " do" << misc::incendl << e.body_get() << ")" << misc::decindent;
  }

  void PrettyPrinter::operator()(const FunctionDec& e)
  {
    if (e.body_get() != nullptr)
      ostr_ << "function ";
    else
      ostr_ << "primitive ";

    ostr_ << e << '(';
    for (auto& var : e.formals_get().decs_get())
      {
        if (escapes_display(ostr_) && var->get_is_escaped())
          {
            ostr_ << "/* escaping */ ";
          }
        const ast::Dec* dec = var;
        ostr_ << *dec;
        if (var->type_name_get() != nullptr)
          ostr_ << " : " << *(var->type_name_get());
        if (var->init_get() != nullptr)
          ostr_ << " := " << *(var->init_get());
        if (var != e.formals_get().decs_get().back())
          {
            ostr_ << ", ";
          }
      }
    ostr_ << ')';
    if (e.result_get() != nullptr)
      ostr_ << " : " << *e.result_get();
    if (e.body_get() != nullptr)
      ostr_ << " =" << misc::incendl << *e.body_get() << misc::decindent;
  }

  void PrettyPrinter::operator()(const IfExp& e)
  {
    ostr_ << "(if " << *e.get_test();
    ostr_ << misc::incendl << "then " << *e.get_thenclause();
    if (e.get_elseclause() != nullptr)
      ostr_ << misc::iendl << "else " << *e.get_elseclause();
    ostr_ << ')' << misc::decindent;
  }

  void PrettyPrinter::operator()(const IntExp& e) { ostr_ << e.value_get(); }

  void PrettyPrinter::operator()(const LetExp& e)
  {
    ostr_ << "let" << misc::incendl;

    for (auto a = e.get_chunkList()->chunks_get().begin();
         a != e.get_chunkList()->chunks_get().end(); ++a)
      {
        if (a != e.get_chunkList()->chunks_get().begin())
          ostr_ << misc::iendl;
        ostr_ << **a;
      }
    ostr_ << misc::decendl << "in" << misc::incendl << *e.get_body()
          << misc::decendl << "end";
  }

  void PrettyPrinter::operator()(const MethodCallExp& e)
  {
    ostr_ << e.get_object();
    ostr_ << e.name_get() << misc::incendl << '(' << misc::incendl;
    for (auto& exp : *e.get_args())
      ostr_ << exp;
    ostr_ << misc::decendl;
    ostr_ << ')' << misc::decindent;
  }

  void PrettyPrinter::operator()(const MethodDec& e)
  {
    ostr_ << "method ";
    ostr_ << e.name_get() << '(' << e.formals_get() << ')';
    if (e.result_get() != nullptr)
      ostr_ << " : " << *e.result_get();
    if (e.body_get() != nullptr)
      ostr_ << " =" << misc::incendl << *e.body_get() << misc::decindent;
  }

  void PrettyPrinter::operator()(const NameTy& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      {
        ostr_ << " /* ";
        ostr_ << e.def_get();
        ostr_ << " */";
      }
  }

  void PrettyPrinter::operator()(const NilExp&) { ostr_ << "nil"; }

  void PrettyPrinter::operator()(const ObjectExp& e)
  {
    ostr_ << "new ";
    ostr_ << *e.value_get();
  }

  void PrettyPrinter::operator()(const OpExp& e)
  {
    ostr_ << "(" << e.left_get() << ' ';
    ostr_ << str(e.oper_get()) << ' ';
    ostr_ << e.right_get() << ")";
  }

  void PrettyPrinter::operator()(const RecordExp& e)
  {
    ostr_ << e.get_type_name()->name_get();

    if (bindings_display(ostr_))
      ostr_ << " /* " << e.get_type_name()->def_get() << " */";

    ostr_ << " { ";
    for (const auto& exp : *e.get_fieldinits_type())
      {
        ostr_ << exp->name_get() << " = " << exp->init_get();
        if (exp != (*e.get_fieldinits_type()).back())
          ostr_ << " , ";
      }
    ostr_ << " }";
  }

  void PrettyPrinter::operator()(const RecordTy& e)
  {
    if (e.get_fields()->size() <= 1)
      {
        ostr_ << " { ";
        for (auto& field : *e.get_fields())
          {
            if (field != e.get_fields()->back())
              ostr_ << *field << " : " << field->type_name_get() << ",";
            else
              ostr_ << *field << " : " << field->type_name_get();
          }
        ostr_ << " }";
      }
    else
      {
        ostr_ << " {" << misc::incendl;
        for (auto& field : *e.get_fields())
          {
            if (field != e.get_fields()->back())
              ostr_ << *field << " : " << field->type_name_get() << ","
                    << misc::iendl;
            else
              ostr_ << *field << " : " << field->type_name_get();
          }
        ostr_ << misc::decendl << "}";
      }
  }

  void PrettyPrinter::operator()(const StringExp& e)
  {
    ostr_ << "\"" << misc::escape(e.value_get()) << "\"";
  }

  void PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << "type " << e << " =" << e.ty_get();
  }

  void PrettyPrinter::operator()(const VarDec& e)
  {
    const ast::Dec& dec = e;
    ostr_ << "var ";
    if (escapes_display(ostr_) && e.get_is_escaped())
      {
        ostr_ << "/* escaping */ " << dec;
        if (e.type_name_get() != nullptr)
          ostr_ << " : " << *e.type_name_get();
        if (e.init_get() != nullptr)
          ostr_ << " := " << *e.init_get();
      }
    else
      {
        ostr_ << dec;
        if (e.type_name_get() != nullptr)
          ostr_ << " : " << *e.type_name_get();
        if (e.init_get() != nullptr)
          ostr_ << " := " << *e.init_get();
      }
  }

  void PrettyPrinter::operator()(const WhileExp& e)
  {
    ostr_ << "while ";
    if (bindings_display(ostr_))
      ostr_ << "/* " << &e << " */ ";
    ostr_ << e.test_get() << " do" << misc::incendl << e.body_get()
          << misc::decindent;
  }

  void PrettyPrinter::operator()(const SeqExp& e)
  {
    if (e.get_exps()->size() == 0)
      {
        ostr_ << "()";
      }
    else if (e.get_exps()->size() == 1)
      {
        ostr_ << *(e.get_exps()->front());
      }
    else
      {
        ostr_ << '(' << misc::incendl;
        for (auto& exp : *e.get_exps())
          {
            if (exp != e.get_exps()->back())
              ostr_ << *exp << ";" << misc::iendl;
            else
              ostr_ << *exp << misc::decendl;
          }
        ostr_ << ')';
      }
  }
} // namespace ast
