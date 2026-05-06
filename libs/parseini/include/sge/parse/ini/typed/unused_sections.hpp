//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_UNUSED_SECTIONS_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_UNUSED_SECTIONS_HPP_INCLUDED

#include <sge/parse/ini/detail/symbol.hpp>
#include <sge/parse/ini/typed/unused_sections_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{
struct unused_sections
{
  SGE_PARSE_INI_DETAIL_SYMBOL
  explicit unused_sections(std::set<std::string> &&);

  std::set<std::string> sections; // NOLINT(misc-non-private-member-variables-in-classes)

  [[nodiscard]]
  SGE_PARSE_INI_DETAIL_SYMBOL bool operator==(unused_sections const &) const noexcept;
};

}

#endif
