/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/devil/load_memory.hpp>
#include <sge/devil/check_error.hpp>
#include <sge/devil/convert_extension.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <IL/il.h>
#include <fcppt/config/external_end.hpp>

sge::devil::optional_error const
sge::devil::load_memory(
	sge::const_raw_range const &_range,
	sge::optional_extension const &_extension
)
{
	if(
		::ilLoadL(
			devil::convert_extension(
				_extension
			),
			_range.begin(),
			fcppt::truncation_check_cast<
				ILuint
			>(
				_range.size()
			)
		)
		== IL_FALSE
	)
		return false;

	return devil::check_error();
}
