//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_SECTION_RESULT_IMPL_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_SECTION_RESULT_IMPL_HPP_INCLUDED

#include <sge/parse/ini/typed/section_result_decl.hpp>
#include <sge/parse/ini/typed/unused_entries.hpp>
#include <fcppt/optional/comparison.hpp> // IWYU pragma: keep
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Record>
sge::parse::ini::typed::section_result<Record>::section_result(
    Record &&_result,
    fcppt::optional::object<sge::parse::ini::typed::unused_entries> &&_unused_entries)
    : result{std::move(_result)}, unused_entries{std::move(_unused_entries)}
{
}

template <typename Record>
bool sge::parse::ini::typed::section_result<Record>::operator==(
    section_result const &) const noexcept = default;

#endif
