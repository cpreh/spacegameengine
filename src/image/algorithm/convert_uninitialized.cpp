/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/src/image/algorithm/convert_uninitialized.hpp>
#include <mizuiro/image/algorithm/uninitialized.hpp>
#include <fcppt/assert/unreachable.hpp>


mizuiro::image::algorithm::uninitialized
sge::image::algorithm::convert_uninitialized(
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	switch(
		_uninitialized
	)
	{
	case sge::image::algorithm::uninitialized::no:
		return
			mizuiro::image::algorithm::uninitialized::no;
	case sge::image::algorithm::uninitialized::yes:
		return
			mizuiro::image::algorithm::uninitialized::yes;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
