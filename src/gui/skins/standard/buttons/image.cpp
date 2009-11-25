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


#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/unit.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <sge/log/headers.hpp>

namespace
{

sge::log::object mylogger(
	sge::log::parameters::inherited(
		sge::gui::global_log(),
		SGE_TEXT("skins: standard: buttons: image")
	)
);

sge::gui::image const &choose_image(
	sge::gui::widgets::buttons::image const &b)
{
	if (b.mouse_over())
	{
		if (b.key_over())
			return *b.hover_keyboard();
		return *b.hover();
	}

	if (b.key_over())
		return *b.keyboard();

	return *b.normal();
}
}

void sge::gui::skins::standard::draw(
	widgets::buttons::image const &b,
	events::invalid_area const &e)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("creating canvas from buffer"));

	b.buffer() = choose_image(b);

	canvas::object c(b.buffer());

	blit_invalid(b,c,e);
}

sge::gui::dim const sge::gui::skins::standard::optimal_size(
	widgets::buttons::image const &b) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_ << SGE_TEXT("returning button dimension ")
		        << b.normal()->size());

	return b.normal()->size();
}
