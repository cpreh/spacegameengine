//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_ENTRY_ERROR_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_ENTRY_ERROR_HPP_INCLUDED

#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <sge/parse/ini/typed/entry_error_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <typeindex>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{

struct entry_error
{
  SGE_PARSE_INI_DETAIL_SYMBOL
  entry_error(std::type_index &&, sge::parse::ini::entry_name &&, sge::parse::ini::value &&);

  std::type_index type; // NOLINT(misc-non-private-member-variables-in-classes)

  std::string name; // NOLINT(misc-non-private-member-variables-in-classes)

  std::string value; // NOLINT(misc-non-private-member-variables-in-classes)

  SGE_PARSE_INI_DETAIL_SYMBOL
  bool operator==(sge::parse::ini::typed::entry_error const &) const noexcept;
};

}

#endif
