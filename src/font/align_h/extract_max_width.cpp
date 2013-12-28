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


#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/extract_max_width.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/optional_max_width.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/align_h/variant.hpp>
#include <fcppt/variant/apply_unary.hpp>


sge::font::align_h::optional_max_width const
sge::font::align_h::extract_max_width(
	sge::font::align_h::variant const &_variant
)
{
	struct visitor
	{
		typedef
		sge::font::align_h::optional_max_width
		result_type;

		result_type
		operator()(
			sge::font::align_h::left const &_left
		) const
		{
			return
				_left.max_width();
		}

		result_type
		operator()(
			sge::font::align_h::center const &_center
		) const
		{
			return
				sge::font::align_h::optional_max_width(
					_center.max_width()
				);
		}

		result_type
		operator()(
			sge::font::align_h::right const &_right
		) const
		{
			return
				sge::font::align_h::optional_max_width(
					_right.max_width()
				);
		}
	};

	return
		fcppt::variant::apply_unary(
			visitor(),
			_variant
		);
}
