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


#include <sge/font/align_h/center_fwd.hpp>
#include <sge/font/align_h/left_fwd.hpp>
#include <sge/font/align_h/right_fwd.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/convert/align_h.hpp>
#include <fcppt/variant/apply_unary.hpp>


UINT
sge::gdifont::convert::align_h(
	sge::font::align_h::variant const &_align_h
)
{
	struct visitor
	{
		typedef
		UINT
		result_type;

		result_type
		operator()(
			sge::font::align_h::left const &
		) const
		{
			return
				DT_LEFT;
		}

		result_type
		operator()(
			sge::font::align_h::center const &
		) const
		{
			return
				DT_CENTER;
		}

		result_type
		operator()(
			sge::font::align_h::right const &
		) const
		{
			return
				DT_RIGHT;
		}
	};

	return
		fcppt::variant::apply_unary(
			visitor(),
			_align_h
		);
}
