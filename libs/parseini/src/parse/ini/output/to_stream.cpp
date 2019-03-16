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
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/output/to_stream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


void
sge::parse::ini::output::to_stream(
	std::ostream &_stream,
	sge::parse::ini::start const &_result
)
{
	for(
		sge::parse::ini::section const &section
		:
		_result.sections
	)
	{
		_stream
			<< '['
			<< section.name
			<< ']'
			<< '\n';

		for(
			sge::parse::ini::entry const &entry
			:
			section.entries
		)
			_stream
				<< '\t'
				<< entry.name
				<< '='
				<< entry.value
				<< '\n';
	}
}
