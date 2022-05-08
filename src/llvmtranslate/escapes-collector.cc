#include <ast/all.hh>
#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>
#include <llvmtranslate/escapes-collector.hh>

namespace llvmtranslate
{
  /// The frame builder collects all the local/formal variables inside a
  /// function, and stores them in a map.
  /// It's used for the EscapesCollector, in order to avoid collecting
  /// local variables escaped by callee functions.

  class FrameBuilder
    : public ast::DefaultConstVisitor
    , public ast::NonObjectConstVisitor
  {
  public:
    /// Super class.
    using super_type = ast::DefaultConstVisitor;
    /// Import overloaded operator() methods.
    using super_type::operator();

    frame_map_type& frame_get() { return frame_; }
//assoc varloc <=> func
    void operator()(const ast::FunctionDec& e) override
    {
      // FIXME: Some code was deleted here.
    }

    void operator()(const ast::VarDec& e) override
    {
      // FIXME: Some code was deleted here.
    }

  private:
    /// Current visiting function.
    // FIXME: Some code was deleted here.
    

    /// Associate a set of variables with their function.
    frame_map_type frame_;
  };

  frame_map_type build_frame(const ast::Ast& ast)
  {
    FrameBuilder builder;
    builder(ast);

    return std::move(builder.frame_get());
  }

  /// LLVM IR doesn't support static link and nested functions.
  /// In order to translate those functions to LLVM IR, we use a technique
  /// called Lambda Lifting, which consists in passing a pointer to
  /// the escaped variables to the nested function using that variable.
  ///
  /// In order to do that, we need a visitor to collect these kind of
  /// variables and associate them to each function.

  class EscapeCollector
    : public ast::DefaultConstVisitor
    , public ast::NonObjectConstVisitor
  {
  public:
    /// Super class.
    using super_type = ast::DefaultConstVisitor;
    /// Import overloaded operator() methods.
    using super_type::operator();

    EscapeCollector(frame_map_type frame)
      : did_modify_{false}
      , escaped_{}
      , frame_{std::move(frame)}
    {}

    escaped_map_type& escaped_get() { return escaped_; }

    void operator()(const ast::FunctionChunk& e) override
    {
      // Iterate on the chunk in order to iteratively collect all the callee
      // functions' escaped variables.
      did_modify_ = !e.empty();
      while (did_modify_)
        {
          did_modify_ = false;
          super_type::operator()(e);
        }
    }
//func vers variable escaped lambda lifting
    void operator()(const ast::FunctionDec& e) override
    {
      // Keep track of the current function
      // FIXME: Some code was deleted here.
    }

    void operator()(const ast::CallExp& e) override
    {
      super_type::operator()(e);

      // Escaped[current] += escaped[all of the callees] - locals/formals
      // FIXME: Some code was deleted here.

      // Check whether there are any newly collected escaped variables.
      // If there are, mark the iteration as modified.
      // FIXME: Some code was deleted here.
    }

    void operator()(const ast::SimpleVar& e) override
    {
      // Associate escaped variables declared in parent frames with their
      // functions
      // FIXME: Some code was deleted here.
    }

  private:
    /// Whether any modification was done during the iteration.
    bool did_modify_ = false;

    /// Associate a set of variables with their function.
    escaped_map_type escaped_;

    /// The map containing the frame of each function.
    frame_map_type frame_;

    /// Current visiting function.
    // FIXME: Some code was deleted here.
  };

  escaped_map_type collect_escapes(const ast::Ast& ast)
  {
    auto frame = build_frame(ast);
    EscapeCollector collect{std::move(frame)};
    collect(ast);

    return std::move(collect.escaped_get());
  }

} // namespace llvmtranslate
