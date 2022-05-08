#pragma once

#include <ast/fwd.hh>
#include <llvmtranslate/fwd.hh>

namespace llvmtranslate
{
  /// Collect all the local variables used in a function.
  /// This is used for the escape collector.
  frame_map_type build_frame(const ast::Ast& ast);

  /// Collect all escapes for every function in the ast, and store it in a map.
  /// This is used for Lambda Lifting.
  escaped_map_type collect_escapes(const ast::Ast& ast);

} // namespace llvmtranslate
