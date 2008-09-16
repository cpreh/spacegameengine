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


#include <sge/log/level_string.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <boost/array.hpp>
#include <algorithm>

namespace
{

typedef boost::array<
	sge::string,
	sge::log::level::size
> name_array;

name_array const names = {
{
	SGE_TEXT("debug"),
	SGE_TEXT("info"),
	SGE_TEXT("warning"),
	SGE_TEXT("error"),
	SGE_TEXT("fatal")
} };

}

sge::log::level::type
sge::log::level_from_string(
	string const &str)
{
	name_array::const_iterator const it =
		std::find(names.begin(), names.end(), str);
	if(it == names.end())
		throw exception(
			SGE_TEXT("level_from_string(): \"")
			+ str
			+ SGE_TEXT("\" not found!"));
	return static_cast<level::type>(
		std::distance(
			static_cast<name_array const &>(
				names).begin(),
			it));
}

sge::string const
sge::log::level_to_string(
	level::type const level_)
{
	return names.at(
		static_cast<name_array::size_type>(
			level_));
}
