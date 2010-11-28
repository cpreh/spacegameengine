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


#include <sge/gui/canvas/font_drawer.hpp>
#include <sge/font/rect.hpp>
#include <sge/image/algorithm/transform.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/image/view/sub.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include "log.hpp"
#include "utility/font_blitter.hpp"

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sge::gui::canvas::global_log(),
		FCPPT_TEXT("font_drawer")
	)
);

}

sge::gui::canvas::font_drawer::font_drawer(
	image_view &texture_,
	color const color_,
	optional_character_pos const &character_pos_,
	point *const point_
)
:
	texture_(texture_),
	color_(color_),
	counter_(0),
	character_pos_(character_pos_),
	point_(point_)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("instantiated")
	);
}

void
sge::gui::canvas::font_drawer::begin_rendering(
	size_type const /*buffer_chars*/,
	font::pos const &/*pos*/,
	font::dim const &/*size*/
)
{
}

void
sge::gui::canvas::font_drawer::draw_char(
	sge::font::text::char_type const,
	font::pos const &pos,
	font::const_image_view const &data
)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("drawing char")
	);

	image_view const sub_view(
		sge::image::view::sub(
			texture_,
			fcppt::math::box::structure_cast<
				sge::image::rect
			>(
				sge::font::rect(
					pos,
					fcppt::math::dim::structure_cast<
						sge::font::dim
					>(
						sge::image::view::dim(
							data
						)
					)
				)
			)
		)
	);

	if (character_pos_)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_
				<< FCPPT_TEXT("counter: ") << counter_ << FCPPT_TEXT(" | ")
				<< FCPPT_TEXT("character pos: ") << *character_pos_
		);
	}
	else
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_
				<< FCPPT_TEXT("character position invalid")
		);
	}

	if (character_pos_ && counter_++ == *character_pos_)
	{
		*point_ = fcppt::math::vector::structure_cast<point>(pos);

		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_
				<< FCPPT_TEXT("found character!")
		);
	}

	sge::image::algorithm::transform(
		data,
		sub_view,
		utility::font_blitter(
			color_
		)
	);
}

void
sge::gui::canvas::font_drawer::end_rendering()
{
}
