//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_START_RESULT_DECL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_START_RESULT_DECL_HPP_INCLUDED

#include <sge/parse/ini/typed/start_result_fwd.hpp> // IWYU pragma: keep
#include <sge/parse/ini/typed/unused_sections.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sge::parse::ini::typed
{
template<typename Record>
struct start_result
{
  start_result(Record &&, fcppt::optional::object<sge::parse::ini::typed::unused_sections> &&);

  Record result; // NOLINT(misc-non-private-member-variables-in-classes)

  fcppt::optional::object<sge::parse::ini::typed::unused_sections> unused_sections; // NOLINT(misc-non-private-member-variables-in-classes)

  [[nodiscard]] bool operator==(start_result const &) const noexcept;
};

template <typename Record>
start_result(Record &&) -> start_result<Record>;

}

#endif
