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


#include "align_pos_v.hpp"
#include "align_pos_h.hpp"
#include <sge/font/char_metric.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/text/char_space.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/drawer.hpp>
#include <sge/font/text/height.hpp>
#include <sge/font/text/line_width.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/size.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sge::font::text::part const
sge::font::text::draw(
	font::metrics &_metrics,
	text::drawer &_drawer,
	text::string const &_text,
	font::rect const &_bounding_box,
	text::align_h::type const _align_h,
	text::align_v::type const _align_v,
	text::flags_field const &_flags
)
{
	unit const height(
		text::height(
			_metrics
		)
	);

	if(
		_text.empty()
		|| height > _bounding_box.size().h()
	)
		return
			font::text::part(
				dim::null(),
				_text.begin(),
				_text.begin()
			);

	font::text::part const total_size(
		font::text::size(
			_metrics,
			_text.begin(),
			_text.end(),
			_bounding_box.size(),
			_flags
		)
	);

	font::pos pos = _bounding_box.pos();

	font::text::align_pos_v(
		pos,
		_bounding_box.size(),
		total_size,
		_align_v
	);

	font::text::align_pos_h(
		pos,
		_bounding_box.size(),
		total_size,
		_align_h
	);

	_drawer.begin_rendering(
		_text.size(),
		pos,
		total_size.size()
	);

	text::string::const_iterator sbeg(
		_text.begin()
	);

	while(
		sbeg != total_size.next_begin()
	)
	{
		font::text::part const line_size(
			font::text::line_width(
				_metrics,
				sbeg,
				_text.end(),
				_bounding_box.size().w(),
				_flags
			)
		);

		pos.x() = _bounding_box.pos().x();

		font::text::align_pos_h(
			pos,
			_bounding_box.size(),
			line_size,
			_align_h
		);

		for(
			;
			sbeg != line_size.end();
			++sbeg
		)
		{
			char_metric_ptr const cm(
				_metrics.load_char(
					*sbeg
				)
			);

			_drawer.draw_char(
				*sbeg,
				pos + cm->offset(),
				cm->pixmap()
			);

			pos.x() +=
				font::text::char_space(
					_metrics,
					*sbeg
				);
		}

		sbeg = line_size.next_begin();

		pos.y() += height;
	}

	_drawer.end_rendering();

	return total_size;
}
