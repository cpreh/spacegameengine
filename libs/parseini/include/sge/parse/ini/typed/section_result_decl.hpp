//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_SECTION_RESULT_DECL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_SECTION_RESULT_DECL_HPP_INCLUDED

#include <sge/parse/ini/typed/section_result_fwd.hpp> // IWYU pragma: keep
#include <sge/parse/ini/typed/unused_entries.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sge::parse::ini::typed
{
template<typename Record>
struct section_result
{
  section_result(Record &&, fcppt::optional::object<sge::parse::ini::typed::unused_entries> &&);

  Record result; // NOLINT(misc-non-private-member-variables-in-classes)

  fcppt::optional::object<sge::parse::ini::typed::unused_entries> unused_entries; // NOLINT(misc-non-private-member-variables-in-classes)

  [[nodiscard]] bool operator==(section_result const &) const noexcept;
};

template <typename Record>
section_result(Record &&) -> section_result<Record>;

}

#endif
