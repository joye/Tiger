/**
 ** Checking ast::Ast and ast::PrettyPrinter.
 */

#include <ostream>

#include <ast/all.hh>
#include <ast/libast.hh>

using namespace ast;

int main()
{
  const Location& loc = Location();

  std::cout << "First test...\n";
  {
    auto exps = new exps_type{
      new AssignExp(loc, new SimpleVar(loc, "a"), new IntExp(loc, 5)),
      new OpExp(loc, new SimpleVar(loc, "a"), OpExp::Oper::add,
                new IntExp(loc, 1))};
    Exp* exp = new SeqExp(loc, exps);
    std::cout << *exp << '\n';
    delete exp;
  }

  std::cout << "Second test...\n";
  {
    // Argument of a function call: `a'.
    auto exps = new exps_type{new SimpleVar(loc, "a")};
    // Declaration of the function: `function f () : int = g (a)'
    FunctionDec* fundec =
      new FunctionDec(loc, "f", new VarChunk(loc), new NameTy(loc, "int"),
                      new CallExp(loc, "g", exps));

    FunctionChunk* funchunk = new FunctionChunk(loc);
    funchunk->emplace_back(*fundec);

    ChunkList* chunks = new ChunkList(loc);
    chunks->emplace_back(funchunk);

    Exp* exp = new LetExp(loc, chunks, new CallExp(loc, "f", new exps_type()));
    std::cout << *exp << '\n';
    delete exp;
  }

  std::cout << "Third test...\n";
  {
    // Test declaration of function with formal parameters
    // Argument of a function call: `a'.
    auto exps = new exps_type{new SimpleVar(loc, "a")};
    // Argument list of the function
    auto formals =
      new VarChunk::Ds{new VarDec(loc, "a", new NameTy(loc, "int"), nullptr),
                       new VarDec(loc, "b", new NameTy(loc, "int"), nullptr)};
    // Declaration of the function:
    // `function f (a : int, b : int) : int = g (a)'.
    FunctionDec* fundec =
      new FunctionDec(loc, "f", new VarChunk(loc, formals),
                      new NameTy(loc, "int"), new CallExp(loc, "g", exps));

    FunctionChunk* funchunk = new FunctionChunk(loc);
    funchunk->emplace_back(*fundec);

    ChunkList* chunks = new ChunkList(loc);
    chunks->emplace_back(funchunk);

    Exp* exp = new LetExp(loc, chunks, new CallExp(loc, "f", new exps_type()));
    std::cout << *exp << '\n';
    delete exp;
  }
}
