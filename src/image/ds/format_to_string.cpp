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


#include <sge/image/ds/format.hpp>
#include <sge/image/ds/format_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/preprocessor/stringize.hpp>


fcppt::string const
sge::image::ds::format_to_string(
	sge::image::ds::format::type const _format
)
{
#define SGE_IMAGE_DS_FORMAT_TO_STRING_CASE(\
	fmt \
) \
case sge::image::ds::format::fmt: \
	return FCPPT_PP_STRINGIZE(fmt)

	switch(
		_format
	)
	{
	SGE_IMAGE_DS_FORMAT_TO_STRING_CASE(d16);
	SGE_IMAGE_DS_FORMAT_TO_STRING_CASE(d32);
	SGE_IMAGE_DS_FORMAT_TO_STRING_CASE(d24s8);
	case sge::image::ds::format::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
