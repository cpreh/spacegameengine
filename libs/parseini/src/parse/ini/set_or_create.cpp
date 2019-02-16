/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/get_or_create_entry.hpp>
#include <sge/parse/ini/get_or_create_section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/set_or_create.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


void
sge::parse::ini::set_or_create(
	sge::parse::ini::start &_start,
	sge::parse::ini::section_name const &_section_name,
	sge::parse::ini::entry_name const &_entry_name,
	sge::parse::ini::value const &_value
)
{
	sge::parse::ini::get_or_create_entry(
		sge::parse::ini::get_or_create_section(
			_start,
			_section_name
		),
		_entry_name,
		sge::parse::ini::value(
			std::string{}
		)
	).value =
		_value.get();
}
