//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/entry.hpp> // NOLINT(misc-include-cleaner)
#include <sge/parse/ini/get_or_create_section.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/section_name_equal.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/make_if.hpp>

fcppt::reference<sge::parse::ini::section> sge::parse::ini::get_or_create_section(
    fcppt::reference<sge::parse::ini::start> const _start,
    sge::parse::ini::section_name const &_section_name)
{
  sge::parse::ini::section_vector &sections(_start.get().sections);

  return fcppt::optional::from(
      fcppt::algorithm::find_by_opt<fcppt::reference<sge::parse::ini::section>>(
          sections,
          [&_section_name](sge::parse::ini::section &_section)
          {
            return fcppt::optional::make_if(
                sge::parse::ini::section_name_equal{fcppt::make_cref(_section_name)}(_section),
                [&_section] { return fcppt::make_ref(_section); });
          }),
      [&_section_name, &sections]
      {
        // NOLINTNEXTLINE(hicpp-use-emplace,modernize-use-emplace)
        sections.push_back(sge::parse::ini::section(sge::parse::ini::section_name{_section_name}));

        return fcppt::make_ref(sections.back());
      });
}
