//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_ENTRY_HPP_INCLUDED
#define SGE_PARSE_INI_ENTRY_HPP_INCLUDED

#include <sge/parse/ini/entry_fwd.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini
{

struct entry
{
  SGE_PARSE_INI_DETAIL_SYMBOL
  entry(sge::parse::ini::entry_name &&, sge::parse::ini::value &&);

  std::string name; // NOLINT(misc-non-private-member-variables-in-classes)

  std::string value; // NOLINT(misc-non-private-member-variables-in-classes)
};

SGE_PARSE_INI_DETAIL_SYMBOL
bool operator==(sge::parse::ini::entry const &, sge::parse::ini::entry const &);

}

#endif
