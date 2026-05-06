//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_START_ERROR_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_START_ERROR_HPP_INCLUDED

#include <sge/parse/ini/detail/symbol.hpp>
#include <sge/parse/ini/typed/duplicate_section.hpp>
#include <sge/parse/ini/typed/section_start_error.hpp>
#include <sge/parse/ini/typed/start_error_fwd.hpp> // IWYU pragma: keep
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{

struct start_error
{
  using variant = fcppt::variant::object<
      std::vector<sge::parse::ini::typed::duplicate_section>,
      std::vector<sge::parse::ini::typed::section_start_error>>;

  SGE_PARSE_INI_DETAIL_SYMBOL
  explicit start_error(variant &&);

  variant variant_; // NOLINT(misc-non-private-member-variables-in-classes)

  SGE_PARSE_INI_DETAIL_SYMBOL
  bool operator==(sge::parse::ini::typed::start_error const &) const noexcept;
};

}

#endif
