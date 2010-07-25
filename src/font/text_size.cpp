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


#include <sge/font/text_size.hpp>
#include <sge/font/line_width.hpp>
#include <sge/font/text_part.hpp>
#include <sge/font/height.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/dim.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>

sge::font::text_part const
sge::font::text_size(
	font::object const &_object,
	string::const_iterator sbeg,
	string::const_iterator const send,
	dim const &max_sz,
	flags_field const &_flags
)
{
	dim sz(
		dim::null()
	);

	unit const height(
		font::height(
			_object
		)
	);

	while(
		sbeg != send
		&& sz.h() + height <= max_sz.h()
	)
	{
		font::text_part const line_size(
			font::line_width(
				_object,
				sbeg,
				send,
				max_sz.w(),
				_flags
			)
		);

		unit const line_w(
			line_size.size().w()
		);

		sz.w() = std::max(sz.w(), line_w);

		sz.h() += height;

		sbeg = line_size.next_begin();

		if(
			_flags & flags::no_multi_line
		)
			break;
	}

	return
		font::text_part(
			sz,
			sbeg,
			sbeg
		);
}

sge::font::text_part const
sge::font::text_size(
	font::object const &_object,
	font::string const &_string,
	dim const &_max_sz,
	flags_field const &_flags
)
{
	return
		font::text_size(
			_object,
			_string.begin(),
			_string.end(),
			_max_sz,
			_flags
		);
}


