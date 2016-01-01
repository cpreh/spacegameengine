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


#include <sge/font/exception.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/parameters_to_string.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/unit.hpp>
#include <sge/gdifont/create_font.hpp>
#include <sge/gdifont/delete_object_deleter.hpp>
#include <sge/gdifont/hfont_unique_ptr.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::gdifont::hfont_unique_ptr
sge::gdifont::create_font(
	sge::font::parameters const &_parameters
)
{
	HFONT const result(
		CreateFont(
			fcppt::optional::maybe(
				_parameters.ttf_size(),
				fcppt::const_(
					0
				),
				[](
					sge::font::ttf_size const _size
				)
				-> int
				{
					// TODO: convert this properly!
					return
						_size;
				}
			),
			0, // width
			0, // escapement
			0, // orientation
			fcppt::optional::maybe(
				_parameters.weight(),
				fcppt::const_(
					0
				),
				[](
					sge::font::weight::unit const _weight
				)
				{
					return
						fcppt::cast::to_signed(
							_weight
						);
				}
			),
			_parameters.italic()
			?
				TRUE
			:
				FALSE
			,
			FALSE, // underline
			FALSE, // strikeout
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			fcppt::from_optional(
				_parameters.family(),
				[]{
					return
						fcppt::string();
				}
			).c_str()
		)
	);

	if(
		result
		==
		nullptr
	)
		throw
			sge::font::exception{
				FCPPT_TEXT("Unable to load GDI font: ")
				+
				sge::font::parameters_to_string(
					_parameters
				)
			};

	return
		sge::gdifont::hfont_unique_ptr(
			result
		);
}
