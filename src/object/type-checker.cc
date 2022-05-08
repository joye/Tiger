/**
 ** \file object/type-checker.cc
 ** \brief Implementation for object/type-checker.hh.
 */

#include <iostream>
#include <sstream>

#include <ast/all.hh>
#include <object/type-checker.hh>
#include <type/types.hh>

namespace object
{
  TypeChecker::TypeChecker()
    : super_type()
  {
    // Reset the subclasses of Object.  This is required if several
    // trees are processed during the compilation.
    type::Class::object_instance().subclasses_clear();

    // `self' variables are the only valid variables having a null
    // declaration site.  Use this property to tag them as read-only.
    // FIXME: Some code was deleted here. (Optional)
  }

  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void TypeChecker::operator()(ast::SimpleVar& e)
  {
    // FIXME: Some code was deleted here. (Optional)
  }

  void TypeChecker::operator()(ast::FieldVar& e)
  {
    const type::Type* def_type = nullptr;
    // FIXME: Some code was deleted here (Grab type). (Optional)
    auto class_type = dynamic_cast<const type::Class*>(&def_type->actual());

    if (class_type)
      {
        // FIXME: Some code was deleted here. (Optional)
      }
    else
      super_type::operator()(e);
  }

  /*----------------.
  | Visiting /Ty/.  |
  `----------------*/

  // Handle the case of `Object'.
  void TypeChecker::operator()(ast::NameTy& e)
  {
    // FIXME: Some code was deleted here. (Optional)
  }

  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  void TypeChecker::operator()(ast::IfExp& e)
  {
    // We want to handle the following case
    // let
    //   class A {}
    //   class B extends A { method print() = () }
    //   var a :=
    //     if 1 then
    //       new B
    //     else
    //       new A
    // in
    //    a.print() /* error */
    // end
    // FIXME: Some code was deleted here. (Optional)
  }

  void TypeChecker::operator()(ast::OpExp& e)
  {
    // We want to only compare equal static object types.
    // Otherwise, the desugarer emits wrong code on:
    //
    // let
    //   class A {}
    //   class B extends A {}
    //   var a := new A
    //   var b := new B
    // in
    //   a = b
    // end
    // FIXME: Some code was deleted here. (Optional)
  }

  void TypeChecker::operator()(ast::ObjectExp& e)
  {
    // FIXME: Some code was deleted here. (Optional)
  }

  void TypeChecker::operator()(ast::MethodCallExp& e)
  {
    // FIXME: Some code was deleted here. (Optional)
  }

  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/

  void TypeChecker::operator()(ast::TypeChunk& e)
  {
    // Visit the header and the body of the typechunk, as in
    // type::TypeChecker.
    super_type::operator()(e);

    // However, class members are not considered part of the body of
    // their class here; they are processed separately to allow valid
    // uses of the class from its members.
    for (ast::TypeDec* typedec : e)
      {
        ast::Ty& ty = typedec->ty_get();
        if (auto classty = dynamic_cast<ast::ClassTy*>(&ty))
          visit_dec_members(*classty);
      }
  }

  /*----------------------.
  | Visiting MethodChunk. |
  `----------------------*/

  void TypeChecker::operator()(ast::MethodChunk& e)
  {
    precondition(within_class_body_p_);
    within_class_body_p_ = false;

    // Two passes: once on headers, then on bodies.
    for (ast::MethodDec* m : e)
      visit_dec_header(*m);
    for (ast::MethodDec* m : e)
      visit_dec_body(*m);

    within_class_body_p_ = true;
  }

  // Store the type of this method.
  void TypeChecker::visit_dec_header(ast::MethodDec& e)
  {
    assertion(current_);

    // FIXME: Some code was deleted here. (Optional)

    // Check for multiple definitions in the current class.
    for (const type::Method* m : current_->meths_get())
      if (m->name_get() == e.name_get())
        return error(e, "method multiply defined", e.name_get());

    // Check for signature conformance w.r.t. super class, if applicable.
    const auto* super_meth_type =
      dynamic_cast<const type::Method*>(current_->meth_type(e.name_get()));
    // FIXME: Some code was deleted here. (Optional)
  }

  // Type check this method's body.
  void TypeChecker::visit_dec_body(ast::MethodDec& e)
  {
    visit_routine_body<type::Method>(e);
  }

  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void TypeChecker::operator()(ast::VarDec& e)
  {
    // Signal that we are not directly inside a class' body, to avoid binding
    // spurious members.
    //
    // For example:
    // let
    //   class A =
    //   {
    //     var a := let var b := 0 in b end
    //   }
    //   var toto := new A
    // in
    //   toto.a /* Valid */
    //   toto.b /* Invalid */
    // end
    bool saved_within_class_body = within_class_body_p_;
    within_class_body_p_ = false;
    super_type::operator()(e);
    within_class_body_p_ = saved_within_class_body;

    /* If we are directly inside a class declaration then E is an attribute:
       record it into the CURRENT_ class.  */
    if (within_class_body_p_)
      {
        assertion(current_);

        if (current_->attr_type(e.name_get()))
          error(e, "attribute multiply defined", e.name_get());
        else
          current_->attr_add(&e);
      }
  }

  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  // Don't handle members, as visit_dec_members is in charge of this task.
  void TypeChecker::operator()(ast::ClassTy& e)
  {
    // FIXME: Some code was deleted here (Create class). (Optional)

    // FIXME: Some code was deleted here (Set the type of the super class). (Optional)

    // FIXME: Some code was deleted here (Recursively update the list of subclasses of the super classes). (Optional)
  }

  // Handle the members of a class.
  void TypeChecker::visit_dec_members(ast::ClassTy& e)
  {
    assertion(!within_class_body_p_); // Should be false by the time we get here
    const type::Type* type = nullptr;
    // FIXME: Some code was deleted here. (Optional)

    assertion(type);
    auto class_type = dynamic_cast<const type::Class*>(type);
    assertion(class_type);

    type::Class* saved_class_type = current_;
    within_class_body_p_ = true;
    // Make the type writable, so that we can add references to the
    // types of the members.
    current_ = const_cast<type::Class*>(class_type);
    e.chunks_get().accept(*this);

    // Set back the status we had before we visited the members.
    current_ = saved_class_type;
    within_class_body_p_ = false;
  }

} // namespace object
