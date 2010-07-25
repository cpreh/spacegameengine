/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/font/line_width.hpp>
#include <sge/font/object.hpp>
#include <sge/font/height.hpp>
#include <sge/font/char_space.hpp>
#include <sge/font/text_part.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>
#include <locale>

sge::font::text_part const
sge::font::line_width(
	sge::font::object const &_object,
	fcppt::string::const_iterator sbeg,
	fcppt::string::const_iterator const send,
	unit const _max_width,
	flags_field const &_flags
)
{
	unit
		width(0),
		last_width(0);

	unit const height(
		font::height(
			_object
		)
	);

	fcppt::string::const_iterator last_white = sbeg;

	for(
		;
		sbeg != send;
		++sbeg
	)
	{
		if(
			*sbeg == FCPPT_TEXT('\n')
		)
			return
				font::text_part(
					dim(
						width,
						height
					),
					sbeg,
					boost::next(
						sbeg
					)
				);

		if(
			std::isspace(
				*sbeg,
				std::locale()
			)
		)
		{
			last_white = sbeg;

			last_width = width;
		}

		unit const new_width(
			width
			+ font::char_space(
				_object,
				*sbeg
			)
		);

		if(
			new_width > _max_width
		)
			return
				last_width
				&& !(_flags & flags::no_line_wrap)
				?
					font::text_part(
						font::dim(
							last_width,
							height
						),
						last_white,
						boost::next(
							last_white
						)
					)
				:
					font::text_part(
						font::dim(
							width,
							height
						),
						sbeg,
						sbeg
					);
		width = new_width;
	}

	return
		font::text_part(
			font::dim(
				width,
				height
			),
			send,
			send
		);
}
