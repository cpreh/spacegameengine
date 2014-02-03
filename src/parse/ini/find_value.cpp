/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
