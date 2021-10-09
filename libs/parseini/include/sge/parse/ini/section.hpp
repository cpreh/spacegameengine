//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_SECTION_HPP_INCLUDED
#define SGE_PARSE_INI_SECTION_HPP_INCLUDED

#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/section_fwd.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini
{

struct section
{
  SGE_PARSE_INI_DETAIL_SYMBOL
  explicit section(sge::parse::ini::section_name &&);

  SGE_PARSE_INI_DETAIL_SYMBOL
  section(sge::parse::ini::section_name &&, sge::parse::ini::entry_vector &&);

  std::string name; // NOLINT(misc-non-private-member-variables-in-classes)

  sge::parse::ini::entry_vector entries; // NOLINT(misc-non-private-member-variables-in-classes)
};

SGE_PARSE_INI_DETAIL_SYMBOL
bool operator==(sge::parse::ini::section const &, sge::parse::ini::section const &);

}

#endif
