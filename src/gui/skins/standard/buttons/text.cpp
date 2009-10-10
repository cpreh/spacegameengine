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


#include "../../../utility/unlimited_text_size.hpp"
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/internal_color.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/colors.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <sge/math/box/output.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins: standard: buttons: text"),
	false);
}

void sge::gui::skins::standard::draw(
	widgets::buttons::text const &b,
	events::invalid_area const &e)
{
	if (b.size() == dim::null())
		return;

	resize_buffer(b);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("creating canvas from buffer"));
	canvas::object c(b.buffer());

	typedef internal_color::format::channel_type channel;

	// Background
	c.draw_rect(
		rect(
			rect::pos_type::null(),
			c.size()
		),
		b.mouse_over() 
			? internal_color(
				sge::image::color::init::red = static_cast<channel>(0xee),
				sge::image::color::init::green = static_cast<channel>(0xeb),
				sge::image::color::init::blue = static_cast<channel>(0xe7),
				sge::image::color::init::alpha = static_cast<channel>(0xff))
			: internal_color(
				sge::image::color::init::red = static_cast<channel>(0xdc),
				sge::image::color::init::green = static_cast<channel>(0xda),
				sge::image::color::init::blue = static_cast<channel>(0xd5),
				sge::image::color::init::alpha = static_cast<channel>(0xff)
			),
		canvas::rect_type::solid);
	
	c.draw_line(
		point(0,0),
		point(c.size().w()-1,0),
		sge::image::colors::white()
	);

	c.draw_line(
		point(0,0),
		point(0,c.size().h()-1),
		sge::image::colors::white()
	);

	c.draw_line(
		point(c.size().w()-2,1),
		point(c.size().w()-2,c.size().h()-2),
		internal_color(
			sge::image::color::init::red = static_cast<channel>(0x9e),
			sge::image::color::init::green = static_cast<channel>(0x9a),
			sge::image::color::init::blue = static_cast<channel>(0x91),
			sge::image::color::init::alpha = static_cast<channel>(0xff)
		)
	);

	c.draw_line(
		point(1,c.size().h()-2),
		point(c.size().w()-2,c.size().h()-2),
		internal_color(
			sge::image::color::init::red = static_cast<channel>(0x9e),
			sge::image::color::init::green = static_cast<channel>(0x9a),
			sge::image::color::init::blue = static_cast<channel>(0x91),
			sge::image::color::init::alpha = static_cast<channel>(0xff)
		)
	);

	c.draw_line(
		point(c.size().w()-1,0),
		point(c.size().w()-1,c.size().h()-1),
		sge::image::colors::black()
	);

	c.draw_line(
		point(0,c.size().h()-1),
		point(c.size().w()-1,c.size().h()-1),
		sge::image::colors::black()
	);
	
	if (b.key_over())
	{
		c.draw_line(
			point(2,2),
			point(c.size().w()-3,2),
			sge::image::colors::black(),
			canvas::line_type::dashed);

		c.draw_line(
			point(c.size().w()-3,2),
			point(c.size().w()-3,c.size().h()-3),
			sge::image::colors::black(),
			canvas::line_type::dashed);

		c.draw_line(
			point(c.size().w()-3,c.size().h()-3),
			point(2,c.size().h()-3),
			sge::image::colors::black(),
			canvas::line_type::dashed);

		c.draw_line(
			point(2,c.size().h()-3),
			point(2,2),
			sge::image::colors::black(),
			canvas::line_type::dashed);
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("drawing text (button \"")
		        << b.caption()
		        << SGE_TEXT("\")"));

	// draw text centered
	c.draw_text(
		standard_font(),
		b.caption(),
		point::null(),
		c.size(),
		font::align_h::center,
		font::align_v::center);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("blitting (button \"")
		        << b.caption()
		        << SGE_TEXT("\")"));

	SGE_LOG_DEBUG(
		mylogger,
		log::_1
			<< SGE_TEXT("source rect is \"")
			<< rect(b.absolute_pos(),c.size())
			<< SGE_TEXT(", invalid rect is ")
			<< e.area());

	blit_invalid(b,c,e);
}

sge::gui::dim const sge::gui::skins::standard::optimal_size(
	widgets::buttons::text const &b) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("calling size hint for button"));

	dim const font_dim = 
		utility::unlimited_text_size(
			standard_font().metrics(),
			b.caption()+SGE_TEXT("aa"));

	return font_dim;
}
