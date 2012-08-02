/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/font/parameters.hpp>
#include <sge/font/parameters_to_string.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


fcppt::string const
sge::font::parameters_to_string(
	sge::font::parameters const &_parameters
)
{
	return
		FCPPT_TEXT("( ")
		FCPPT_TEXT("ttf_size: ")
		+
		(
			_parameters.ttf_size()
			?
				fcppt::insert_to_fcppt_string(
					*_parameters.ttf_size()
				)
			:
				FCPPT_TEXT("default")
		)
		+
		FCPPT_TEXT(", ")
		FCPPT_TEXT("family: ")
		+
		(
			_parameters.family()
			?
				*_parameters.family()
			:
				FCPPT_TEXT("default")
		)
		+
		FCPPT_TEXT(", ")
		FCPPT_TEXT("weight: ")
		+
		(
			_parameters.weight()
			?
				fcppt::insert_to_fcppt_string(
					*_parameters.weight()
				)
			:
				FCPPT_TEXT("default")
		)
		+
		FCPPT_TEXT(", ")
		FCPPT_TEXT("italic: ")
		+
		fcppt::insert_to_fcppt_string(
			_parameters.italic()
		)
		+
		FCPPT_TEXT(" )");
}
