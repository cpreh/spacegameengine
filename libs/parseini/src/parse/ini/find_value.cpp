//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <sge/parse/ini/find_value.hpp>
#include <sge/parse/ini/optional_value.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/section_name_equal.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::parse::ini::optional_value
sge::parse::ini::find_value(
	sge::parse::ini::start const &_start,
	sge::parse::ini::section_name const _section_name,
	sge::parse::ini::entry_name const _entry_name
)
{
	sge::parse::ini::section_vector const &sections(
		_start.sections
	);

	sge::parse::ini::section_vector::const_iterator const section_it(
		std::find_if(
			sections.begin(),
			sections.end(),
			sge::parse::ini::section_name_equal(
				_section_name
			)
		)
	);

	if(
		section_it
		==
		sections.end()
	)
		return
			sge::parse::ini::optional_value();

	sge::parse::ini::entry_vector const &entries(
		section_it->entries
	);

	sge::parse::ini::entry_vector::const_iterator const entry_it(
		std::find_if(
			entries.begin(),
			entries.end(),
			sge::parse::ini::entry_name_equal(
				_entry_name
			)
		)
	);

	return
		entry_it
		==
		entries.end()
		?
			sge::parse::ini::optional_value()
		:
			sge::parse::ini::optional_value(
				sge::parse::ini::value(
					entry_it->value
				)
			)
		;
}
