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


#include "align_pos_v.hpp"
#include "align_pos_h.hpp"
#include <sge/font/draw_text.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/char_metric.hpp>
#include <sge/font/drawer.hpp>
#include <sge/font/text_size.hpp>
#include <sge/font/line_width.hpp>
#include <sge/font/height.hpp>
#include <sge/font/text_part.hpp>
#include <sge/font/exception.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::font::text_part const
sge::font::draw_text(
	font::object const &_object,
	font::string const &text,
	pos const &start_pos,
	dim const &max_sz,
	align_h::type const align_h,
	align_v::type const align_v,
	flags_field const &flags
)
{
	if(
		!_object.drawer()
	)
		throw font::exception(
			FCPPT_TEXT("font::drawer not set in font::draw_text!")
		);

	unit const height(
		font::height(
			_object
		)
	);

	if(
		text.empty()
		|| height > max_sz.h()
	)
		return
			font::text_part(
				dim::null(),
				text.begin(),
				text.begin()
			);

	font::text_size const total_size(
		font::text_size(
			text.begin(),
			text.end(),
			max_sz,
			flags
		)
	);

	pos pos_ = start_pos;

	font::align_pos_v(
		pos_,
		max_sz,
		total_size,
		align_v
	);

	font::string::const_iterator sbeg(
		text.begin()
	);

	object_.drawer()->begin_rendering(
		text.size(),
		pos_,
		total_size.size()
	);

	while(
		sbeg != total_size.next_begin()
	)
	{
		font::text_size const line_size(
			font::line_width(
				sbeg,
				text.end(),
				max_sz.w(),
				flags
			)
		);

		pos_.x() = start_pos.x();

		font::align_pos_h(
			pos_,
			max_sz,
			line_size,
			align_h
		);

		for(
			;
			sbeg != line_size.end();
			++sbeg
		)
		{
			char_metric_ptr const cm(
				_object.metrics()->load_char(
					*sbeg
				)
			);

			_object.drawer()->draw_char(
				*sbeg,
				pos_ + cm->offset(),
				cm->pixmap()
			);

			pos_.x() +=
				font::char_space(
					_object,
					*sbeg
				);
		}

		sbeg = line_size.next_begin();

		pos_.y() += height;
	}

	_object.drawer()->end_rendering();

	return total_size;
}
