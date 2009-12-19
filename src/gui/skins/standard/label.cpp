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


#include "../../utility/unlimited_text_size.hpp"
#include "../../utility/string_square.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/internal_color.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/unit.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <sge/image/colors.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <sge/log/headers.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>

namespace
{

sge::log::object mylogger(
	sge::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("skins::standard::label")
	)
);

}

void sge::gui::skins::standard::draw(
	widgets::label const &b,
	events::invalid_area const &e)
{
	resize_buffer(b);

	SGE_LOG_DEBUG(
		mylogger,
		log::_ << FCPPT_TEXT("creating canvas from buffer"));

	canvas::object c(b.buffer());

	// Background
	/*
	c.draw_rect(
		rect(c.size()),
		internal_color(0xee,0xee,0xee,0xff),
		canvas::rect_type::solid);
		*/
	c.draw_rect(
		rect(
			rect::pos_type::null(),
			c.size()
		),
		sge::image::colors::transparent(),
		canvas::rect_type::solid);

	SGE_LOG_DEBUG(
		mylogger,
		log::_ << FCPPT_TEXT("drawing text (label \"")
		        << b.text()
		        << FCPPT_TEXT("\")"));

	// draw text centered
	c.draw_text(
		standard_font(),
		b.text(),
		point::null(),
		c.size(),
		b.align_h(),
		b.align_v());

	SGE_LOG_DEBUG(
		mylogger,
		log::_ << FCPPT_TEXT("blitting (label \"")
		        << b.text()
		        << FCPPT_TEXT("\")"));

	blit_invalid(
		b,
		c,
		e,
		true);
}

sge::gui::dim const sge::gui::skins::standard::optimal_size(
	widgets::label const &b) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_ << FCPPT_TEXT("calling size hint for label"));

	return
		utility::unlimited_text_size(
			standard_font().metrics(),
			b.static_size()
				? utility::string_square(*b.static_size())
				: b.text());
}
