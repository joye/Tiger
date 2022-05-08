/**
 ** \file parse/fwd.hh
 ** \brief Forward declarations for the parse module.
 */

#pragma once

#include <misc/variant.hh>

// From ast/.
namespace ast
{
  class Exp;
  class ChunkList;

} // namespace ast

namespace parse
{
  // From scantiger.hh.
  class yyFlexLexer;

  // From parsetiger.yy.
  class parser;

  // From location.hh.
  class location;

  // From tiger-parser.hh.
  class TigerParser;

  // From tiger-driver.hh
  class TigerDriver;

  // From tweast.hh
  class Tweast;

  /// Result of a parse: an Exp (*.tig) or a ChunkList (*.tih).
  using ast_type = misc::variant<ast::Exp*, ast::ChunkList*>;

} // namespace parse
