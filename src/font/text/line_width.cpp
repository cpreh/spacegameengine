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


#include <sge/font/text/line_width.hpp>
#include <sge/font/text/height.hpp>
#include <sge/font/text/char_space.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/lit.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <locale>

sge::font::text::part const
sge::font::text::line_width(
	sge::font::metrics &_metrics,
	text::string::const_iterator _sbeg,
	text::string::const_iterator const _send,
	unit const _max_width,
	flags_field const &_flags
)
{
	font::unit
		width(0),
		last_width(0);

	font::unit const height(
		font::text::height(
			_metrics
		)
	);

	font::text::string::const_iterator last_white = _sbeg;

	for(
		;
		_sbeg != _send;
		++_sbeg
	)
	{
		if(
			*_sbeg == SGE_FONT_TEXT_LIT('\n')
		)
			return
				font::text::part(
					font::dim(
						width,
						height
					),
					_sbeg,
					boost::next(
						_sbeg
					)
				);

		if(
			std::isspace(
				*_sbeg,
				std::locale()
			)
		)
		{
			last_white = _sbeg;

			last_width = width;
		}

		font::unit const new_width(
			width
			+
			font::text::char_space(
				_metrics,
				*_sbeg
			)
		);

		if(
			new_width > _max_width
		)
			return
				last_width
				&& !(_flags & flags::no_line_wrap)
				?
					font::text::part(
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
					font::text::part(
						font::dim(
							width,
							height
						),
						_sbeg,
						_sbeg
					);
		width = new_width;
	}

	return
		font::text::part(
			font::dim(
				width,
				height
			),
			_send,
			_send
		);
}
