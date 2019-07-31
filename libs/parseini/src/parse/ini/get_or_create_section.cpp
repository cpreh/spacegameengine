//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/get_or_create_section.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/section_name_equal.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::parse::ini::section &
sge::parse::ini::get_or_create_section(
	sge::parse::ini::start &_start,
	sge::parse::ini::section_name const &_section_name
)
{
	sge::parse::ini::section_vector &sections(
		_start.sections
	);

	sge::parse::ini::section_vector::iterator it(
		std::find_if(
			sections.begin(),
			sections.end(),
			sge::parse::ini::section_name_equal(
				_section_name
			)
		)
	);

	if(
		it == sections.end()
	)
		it =
			sections.insert(
				sections.end(),
				sge::parse::ini::section(
					sge::parse::ini::section_name{
						_section_name
					}
				)
			);

	return *it;
}
