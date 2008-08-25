/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/log/default_formatter.hpp>
#include <sge/log/insert_formatter.hpp>
#include <sge/text.hpp>
#include <boost/array.hpp>

sge::log::const_formatter_ptr const
sge::log::default_formatter(
	level::type const level_)
{
	boost::array<string, level::size>
	const prefix_array = {
	{
		SGE_TEXT("debug"),
		SGE_TEXT("info"),
		SGE_TEXT("warning"),
		SGE_TEXT("error"),
		SGE_TEXT("fatal")
	} };

	return const_formatter_ptr(
		new insert_formatter(
			prefix_array.at(level_)
			+ SGE_TEXT(": %1%\n")));
}
