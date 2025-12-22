//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_UNUSED_ENTRIES_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_UNUSED_ENTRIES_HPP_INCLUDED

#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <sge/parse/ini/typed/unused_entries_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{
struct unused_entries
{
  SGE_PARSE_INI_DETAIL_SYMBOL
  unused_entries(sge::parse::ini::section_name &&, std::set<std::string> &&);

  std::string section_name; // NOLINT(misc-non-private-member-variables-in-classes)

  std::set<std::string> entries; // NOLINT(misc-non-private-member-variables-in-classes)

  [[nodiscard]]
  SGE_PARSE_INI_DETAIL_SYMBOL bool operator==(unused_entries const &) const noexcept;
};

}

#endif
