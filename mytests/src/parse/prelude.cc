#include "parse/tiger-parser.hh"

namespace parse
{
  const char* TigerParser::prelude () const
  {
    return
      "primitive print(string : string)\n"
      "primitive print_err(string : string)\n"
      "primitive print_int(int : int)\n"
      "primitive flush()\n"
      "primitive getchar() : string\n"
      "primitive ord(string : string) : int\n"
      "primitive chr(code : int) : string\n"
      "primitive size(string : string) : int\n"
      "primitive streq(s1 : string, s2 : string) : int\n"
      "primitive strcmp(s1 : string, s2 : string) : int\n"
      "primitive substring(string : string, start : int, length : int) : string\n"
      "primitive concat(fst : string, snd : string) : string\n"
      "primitive not(boolean : int) : int\n"
      "primitive exit(status : int)\n"
    ;
  }
} // namespace parse
