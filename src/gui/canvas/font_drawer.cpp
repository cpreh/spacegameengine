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


#include <sge/gui/canvas/font_drawer.hpp>
#include <sge/font/rect.hpp>
#include <sge/image/algorithm/transform.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/math/box/structure_cast.hpp>
#include <sge/math/box/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include "log.hpp"
#include "utility/font_blitter.hpp"

namespace
{
sge::gui::logger mylogger(sge::gui::canvas::global_log(),SGE_TEXT("font_drawer"),false);
}

sge::gui::canvas::font_drawer::font_drawer(
	image_view &texture_,
	color c,
	optional_character_pos const &character_pos,
	point *const p)
:
	texture_(texture_),
	c(c),
	counter(0),
	character_pos(character_pos),
	p(p)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("instantiated"));
}

void sge::gui::canvas::font_drawer::begin_rendering(
	size_type const /*buffer_chars*/,
	font::pos const &/*pos*/,
	font::dim const /*size*/)
{
}

void sge::gui::canvas::font_drawer::draw_char(
	char_type const, 
	font::pos const &pos, 
	font::const_image_view const &data)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("drawing char"));

	image_view const sub_view = sge::image::view::sub(
		texture_,
		sge::math::box::structure_cast<
			sge::image::rect
		>(
			sge::font::rect(
				pos,
				sge::math::dim::structure_cast<
					sge::font::dim
				>(
					sge::image::view::dim(
						data
					)
				)
			)
		)
	);
	
	if (character_pos)
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("counter: ") << counter << SGE_TEXT(" | ")
			        << SGE_TEXT("character pos: ") << *character_pos);
	}
	else
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("character position invalid"));
	}

	if (character_pos && counter++ == *character_pos)
	{
		*p = math::vector::structure_cast<point>(pos);
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("found character!"));
	}
	
	sge::image::algorithm::transform(
		data,
		sub_view,
		utility::font_blitter(c)
	);
}

void sge::gui::canvas::font_drawer::end_rendering()
{
}
