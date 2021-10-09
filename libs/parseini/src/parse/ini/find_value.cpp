//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <sge/parse/ini/find_value.hpp>
#include <sge/parse/ini/optional_value.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/section_name_equal.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>

sge::parse::ini::optional_value sge::parse::ini::find_value(
    sge::parse::ini::start const &_start,
    sge::parse::ini::section_name const &_section_name,
    sge::parse::ini::entry_name const &_entry_name)
{
  return fcppt::algorithm::find_by_opt<sge::parse::ini::value>(
      _start.sections,
      [&_section_name, &_entry_name](sge::parse::ini::section const &_section)
      {
        return fcppt::optional::join(fcppt::optional::make_if(
            sge::parse::ini::section_name_equal{fcppt::make_cref(_section_name)}(_section),
            [&_section, &_entry_name]
            {
              return fcppt::algorithm::find_by_opt<sge::parse::ini::value>(
                  _section.entries,
                  [&_entry_name](sge::parse::ini::entry const &_entry)
                  {
                    return fcppt::optional::make_if(
                        sge::parse::ini::entry_name_equal{fcppt::make_cref(_entry_name)}(_entry),
                        [&_entry] { return sge::parse::ini::value{_entry.value}; });
                  });
            }));
      });
}
