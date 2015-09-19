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


#include <sge/wininput/cursor/pixmap.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/windows/module_handle.hpp>
#include <awl/backends/windows/system_metrics.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>


sge::wininput::cursor::pixmap::pixmap()
:
	cursor_(
		[]{
			int const
				cursor_width(
					awl::backends::windows::system_metrics(
						SM_CXCURSOR
					)
				),
				cursor_height(
					awl::backends::windows::system_metrics(
						SM_CYCURSOR
					)
				);

			typedef
			std::vector<
				BYTE
			>
			byte_vector;

			static_assert(
				std::is_unsigned<
					BYTE
				>::value,
				"BYTE should be unsigned"
			);

			byte_vector::size_type const size(
				fcppt::math::ceil_div(
					fcppt::cast::size<
						byte_vector::size_type
					>(
						fcppt::cast::to_unsigned(
							cursor_width
							*
							cursor_height
						)
					),
					fcppt::cast::size<
						byte_vector::size_type
					>(
						std::numeric_limits<
							BYTE
						>::digits
					)
				)
			);

			byte_vector const
				and_values(
					size,
					std::numeric_limits<
						BYTE
					>::max()
				),
				xor_values(
					size,
					fcppt::literal<
						BYTE
					>(
						0u
					)
				);

			return
				::CreateCursor(
					awl::backends::windows::module_handle(),
					0,
					0,
					cursor_width,
					cursor_height,
					and_values.data(),
					xor_values.data()
				);
		}()
	)
{

	if(
		cursor_
		==
		NULL
	)
		throw
			sge::input::exception(
				FCPPT_TEXT("CreateCursor() failed!")
			);
}

sge::wininput::cursor::pixmap::~pixmap()
{
	::DestroyCursor(
		cursor_
	);
}

HCURSOR
sge::wininput::cursor::pixmap::get() const
{
	return
		cursor_;
}
