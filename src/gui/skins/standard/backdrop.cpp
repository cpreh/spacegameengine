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


#include "../../utility/blit.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/internal_color.hpp>
#include <sge/text.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins::standard::backdrop"),
	true);
}

void sge::gui::skins::standard::draw(
	widgets::backdrop const &w,
	events::invalid_area const &e)
{
	resize_buffer(w);

	canvas::object c(w.buffer());

	// Background
	c.draw_rect(
		rect(
			rect::point_type::null(),
			c.size()
		),
		internal_color(0xee,0xeb,0xe7,0xff),
		canvas::rect_type::solid);

	blit_invalid(w,c,e);
}

sge::gui::dim const sge::gui::skins::standard::optimal_size(
	widgets::backdrop const &) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("optimal_size called for backdrop, returning null"));
	return dim::null();
}
