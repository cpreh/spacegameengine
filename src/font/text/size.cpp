/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/font/text/size.hpp>
#include <sge/font/text/line_width.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/height.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/dim.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>

sge::font::text::part const
sge::font::text::size(
	sge::font::metrics_ptr const _metrics,
	text::string::const_iterator _sbeg,
	text::string::const_iterator const _send,
	font::dim const &_max_sz,
	text::flags_field const &_flags
)
{
	font::dim sz(
		font::dim::null()
	);

	font::unit const height(
		text::height(
			_metrics
		)
	);

	while(
		_sbeg != _send
		&& sz.h() + height <= _max_sz.h()
	)
	{
		font::text::part const line_size(
			text::line_width(
				_metrics,
				_sbeg,
				_send,
				_max_sz.w(),
				_flags
			)
		);

		font::unit const line_w(
			line_size.size().w()
		);

		sz.w() = std::max(sz.w(), line_w);

		sz.h() += height;

		_sbeg = line_size.next_begin();

		if(
			_flags & text::flags::no_multi_line
		)
			break;
	}

	return
		font::text::part(
			sz,
			_sbeg,
			_sbeg
		);
}

sge::font::text::part const
sge::font::text::size(
	sge::font::metrics_ptr const _metrics,
	font::text::string const &_string,
	font::dim const &_max_sz,
	text::flags_field const &_flags
)
{
	return
		text::size(
			_metrics,
			_string.begin(),
			_string.end(),
			_max_sz,
			_flags
		);
}


