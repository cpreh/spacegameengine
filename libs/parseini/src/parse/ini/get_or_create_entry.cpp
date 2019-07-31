//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/get_or_create_entry.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::parse::ini::entry &
sge::parse::ini::get_or_create_entry(
	sge::parse::ini::section &_section,
	sge::parse::ini::entry_name const &_entry_name,
	sge::parse::ini::value const &_value
)
{
	sge::parse::ini::entry_vector &entries(
		_section.entries
	);

	sge::parse::ini::entry_vector::iterator it(
		std::find_if(
			entries.begin(),
			entries.end(),
			sge::parse::ini::entry_name_equal(
				_entry_name
			)
		)
	);

	if(
		it == entries.end()
	)
		it =
			entries.insert(
				entries.end(),
				sge::parse::ini::entry(
					sge::parse::ini::entry_name{
						_entry_name
					},
					sge::parse::ini::value{
						_value
					}
				)
			);

	return *it;
}
