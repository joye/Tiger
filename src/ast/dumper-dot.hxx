/**
 ** \file ast/dumper-dot.hxx
 ** \brief Implementation of ast::DumperDot.
 */

#pragma once

#include <ast/dumper-dot.hh>
#include <misc/indent.hh>

namespace ast
{
  template <typename T>
  inline void DumperDot::dump(const std::string& field, const T& e)
  {
    const std::string* old_parent_field = parent_field;
    parent_field = &field;
    e.accept(*this);
    parent_field = old_parent_field;
  }
  template <typename T>
  inline void DumperDot::dump(const std::string& field, const T* e)
  {
    if (!e)
      return;
    const std::string* old_parent_field = parent_field;
    parent_field = &field;
    e->accept(*this);
    parent_field = old_parent_field;
  }
  template <typename T>
  inline void DumperDot::dump_list(const std::string& field, const T& l)
  {
    const std::string* old_parent_field = parent_field;
    auto it = l.begin();
    unsigned n = 0;
    while (it != l.end())
      {
        std::ostringstream o;
        o << field;
        if (std::next(it) != l.end() || n > 0)
          o << n++;
        const std::string field_name = o.str();
        parent_field = &field_name;
        (*it++)->accept(*this);
      }
    parent_field = old_parent_field;
  }

  template <typename T> inline void DumperDot::dump_def(const T& e) const
  {
    const auto* d = dynamic_cast<const ast::Ast*>(&e);
    if (!d)
      return;
    ostr_ << parent_id << ":def:s -> " << reinterpret_cast<std::uintptr_t>(d)
          << ":nodename [constraint=false, style=dashed, color=\"dimgray\"]"
          << misc::iendl;
  }

  inline void DumperDot::display_link(unsigned long old_parent_id) const
  {
    if (parent_field)
      ostr_ << old_parent_id << ":" << *parent_field << ":s"
            << " -> " << parent_id << ":nodename:n" << misc::iendl;
  }

  inline void DumperDot::footer_and_link(unsigned long old_parent_id) const
  {
    node_html_footer();
    display_link(old_parent_id);
  }

  template <typename E>
  inline void DumperDot::dump_chunk(const E& e, const std::string& name)
  {
    unsigned long old_parent_id = parent_id;
    parent_id = reinterpret_cast<std::uintptr_t>(&e);
    ostr_ << parent_id << " [label=<" << misc::incendl
          << "<table cellborder='0' cellspacing='0'>" << misc::incendl << "<tr>"
          << misc::incendl;
    inner_fields = 0;
    node_html_port_list(name, e, true);
    ostr_ << misc::decendl << "</tr>" << misc::decendl << "</table>"
          << misc::decendl << ">]" << misc::iendl;
    display_link(old_parent_id);
    dump_list("nodename", e);
    parent_id = old_parent_id;
  }

  namespace
  {
    inline void node_html_begin_inner(std::ostream& ostr, bool list = false)
    {
      ostr << "<td cellpadding='0'>" << misc::incendl
           << "<table border='0' cellborder='" << (list ? 0 : 1) << "'"
           << " cellspacing='0' cellpadding='" << (list ? 0 : 2) << "'>"
           << misc::incendl << "<tr>" << misc::incendl;
    }

    inline void node_html_end_inner(std::ostream& ostr)
    {
      ostr << misc::decendl << "</tr>" << misc::decendl << "</table>"
           << misc::decendl << "</td>";
    }

    inline void node_html_separator(std::ostream& ostr)
    {
      node_html_end_inner(ostr);
      ostr << misc::decendl << "</tr>" << misc::iendl << "<tr>"
           << misc::incendl;
      node_html_begin_inner(ostr);
    }
    inline void node_html_tr(std::ostream& ostr,
                             const std::string& port,
                             const std::string content)
    {
      ostr << "<td port='" << port << "'>" << content << "</td>";
    }
    inline bool ends_with(const std::string& value, const std::string& ending)
    {
      if (ending.size() > value.size())
        return false;
      return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
    inline std::string node_html_color(const std::string& type)
    {
      if (ends_with(type, "Dec"))
        return "red1";
      else if (ends_with(type, "Var"))
        return "orange1";
      else if (ends_with(type, "Ty"))
        return "green3";
      else if (ends_with(type, "Exp"))
        return "blue2";
      return "black";
    }

    template <typename T> std::string html_escape(const T& input)
    {
      std::ostringstream i;
      i << input;
      const std::string& str = i.str();
      std::ostringstream o;
      const std::string& specials = "&<>";
      for (const auto& p : str)
        if (p == '\\')
          o << '\\' << '\\';
        else if (specials.find(p) != std::string::npos)
          o << "&#" << static_cast<int>(static_cast<unsigned char>(p)) << ";";
        else
          o << p;
      return o.str();
    }
  } // namespace

  template <typename T>
  inline unsigned long DumperDot::node_html_header(const T& e,
                                                   const std::string& type)
  {
    unsigned long old_parent_id = parent_id;
    parent_id = reinterpret_cast<std::uintptr_t>(&e);
    ostr_ << parent_id << " [label=<" << misc::incendl
          << "<table border='0' cellborder='0' cellspacing='0' cellpadding='0'"
          << " color='" << node_html_color(type) << "'>" << misc::incendl
          << "<tr>" << misc::incendl;
    node_html_begin_inner(ostr_);
    node_html_tr(ostr_, "nodename", type);
    node_html_separator(ostr_);
    inner_fields = 0;
    return old_parent_id;
  }
  template <typename T>
  inline void DumperDot::node_html_field(const std::string& name,
                                         const T& content,
                                         const std::string& sep)
  {
    std::ostringstream o;
    o << name << ":&nbsp;" << sep << html_escape(content) << sep;
    if (inner_fields++)
      ostr_ << misc::iendl;
    node_html_tr(ostr_, name, o.str());
  }
  inline void DumperDot::node_html_one_port(const std::string& p)
  {
    if (inner_fields++)
      ostr_ << misc::iendl;
    node_html_tr(ostr_, p, p);
  }
  inline void DumperDot::node_html_ports(const std::vector<std::string>& ports)
  {
    if (inner_fields)
      node_html_separator(ostr_);
    inner_fields = 0;
    for (auto p : ports)
      node_html_one_port(p);
  }
  template <typename T>
  inline void DumperDot::node_html_port_list(const std::string& name,
                                             const T& list,
                                             bool chunk)
  {
    if (inner_fields++)
      ostr_ << misc::iendl;
    const std::string ref = chunk ? "nodename" : name;
    node_html_begin_inner(ostr_, true);
    long int size = std::distance(list.begin(), list.end());
    ostr_ << "<td port='" << ref << "' colspan='" << (size ? size : 1) << "'>"
          << name << "</td>";
    if (size > 1)
      {
        ostr_ << misc::decendl << "</tr>" << misc::iendl << "<tr>"
              << misc::incindent;
        for (long int n = 0; n < size; n++)
          ostr_ << misc::iendl << "<td port='" << ref << n << "'>" << n
                << "</td>";
      }
    node_html_end_inner(ostr_);
  }
  inline void DumperDot::node_html_footer() const
  {
    if (!inner_fields)
      ostr_ << "<td></td>";
    node_html_end_inner(ostr_);
    ostr_ << misc::decendl << "</tr>" << misc::decendl << "</table>"
          << misc::decendl << ">]" << misc::iendl;
  }
} // namespace ast
