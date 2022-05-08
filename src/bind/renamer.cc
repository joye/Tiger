/**
 ** \file bind/renamer.cc
 ** \brief Implementation of bind::Renamer.
 */

#include <bind/renamer.hh>

namespace bind
{
  using namespace ast;

  Renamer::Renamer()
    : super_type()
    , new_names_()
  {}

  // DONE: Some code was deleted here.
  void Renamer::operator()(ast::VarDec& e)
  {
    if (new_names_.find(&e) == new_names_.end())
      {
        e.name_set(new_name(e));
        new_names_[&e] = e.name_get();
        super_type::operator()(e);
      }
    else
      {
        super_type::operator()(e);
      }
  }

  void Renamer::operator()(ast::FunctionDec& e)
  {
    if (new_names_.find(&e) == new_names_.end())
      {
        e.name_set(new_name(e));
        new_names_[&e] = e.name_get();
        super_type::operator()(e);
      }
    else
      {
        super_type::operator()(e);
      }
  }

  void Renamer::operator()(ast::TypeDec& e)
  {
    if (new_names_.find(&e) == new_names_.end())
      {
        e.name_set(new_name(e));
        new_names_[&e] = e.name_get();
        super_type::operator()(e);
      }
    else
      {
        super_type::operator()(e);
      }
  }

  void Renamer::operator()(ast::SimpleVar& e)
  {
    if (new_names_.find(e.def_get()) == new_names_.end())
      {
        super_type::operator()(e.def_get());
        e.name_set(new_names_[e.def_get()]);
        super_type::operator()(e);
      }
    else
      {
        e.name_set(new_names_[e.def_get()]);
        super_type::operator()(e);
      }
  }

  void Renamer::operator()(ast::CallExp& e)
  {
    if (new_names_.find(e.def_get()) == new_names_.end())
      {
        super_type::operator()(e.def_get());
        e.name_set(new_names_[e.def_get()]);
        super_type::operator()(e);
      }
    else
      {
        e.name_set(new_names_[e.def_get()]);
        super_type::operator()(e);
      }
  }

  void Renamer::operator()(ast::NameTy& e)
  {
    if (e.def_get() == nullptr)
      {
        return;
      }
    if (new_names_.find(e.def_get()) == new_names_.end())
      {
        super_type::operator()(e.def_get());
        e.name_set(new_names_[e.def_get()]);
        super_type::operator()(e);
      }
    else
      {
        e.name_set(new_names_[e.def_get()]);
        super_type::operator()(e);
      }
  }

} // namespace bind
