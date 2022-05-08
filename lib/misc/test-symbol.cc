/**
 ** Testing the symbols and the symbol tables.
 */

#include <ostream>

#include <misc/contract.hh>
#include <misc/symbol.hh>

using misc::symbol;

int main()
{
  const symbol toto1("toto");
  const symbol toto2("toto");
  const symbol titi1("titi");

  // Checking symbol.
  // DONE: Some code was deleted here (Testing set size).
  std::cout << "toto1: " << toto1 << std::endl;
  assertion(toto1.object_map_size() == toto2.object_map_size());
  assertion(toto1.object_map_size() == 2);
  assertion(toto1.get() == "toto");

  assertion(toto1 == "toto");
  assertion(toto1 != "titi");

  assertion(toto1 == toto2);
  assertion(toto1 != titi1);

  std::string junk = "tata";
  const symbol tata1(junk);
  junk = "toto";
  assertion(tata1 == "tata");
}
