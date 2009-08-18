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
#include "../../utility/blit.hpp"
#include <sge/gui/internal_color.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <sge/image/colors.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/skins/standard.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),SGE_TEXT("skins: standard: edit"),
	false);
}

sge::gui::dim const sge::gui::skins::standard::optimal_size(
	widgets::edit const &w) const
{
	dim const d = utility::unlimited_text_size(
		standard_font().metrics(),
		utility::string_square(w.desired_size()));

	return 
		dim(
			static_cast<unit>(d.w() + 2),
			static_cast<unit>(d.h() + 2));
}

void sge::gui::skins::standard::draw(
	widgets::edit const &w,
	events::invalid_area const &e)
{
	if (w.size() == dim::null())
		return;

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("refreshing edit buffer"));
	// re-render text buffer
	w.refresh();
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("refreshed edit buffer"));
	
	resize_buffer(w);

	canvas::object c(w.buffer());

	typedef internal_color::format::channel_type channel_type;

	// fill completely with background color
	c.draw_rect(
		c.area(),
	//	internal_color(0x55,0x55,0x55,0xff),
		sge::image::colors::white(),
		/*
		internal_color(
			color::init::red = static_cast<channel_type>(0xff),
			color::init::blue = static_cast<channel_type>(0xff),
			color::init::green = static_cast<channel_type>(0xff),
			color::init::alpha = static_cast<channel_type>(0xff)
		),
		*/
		canvas::rect_type::solid);

	dim const scroll_size = 
		w.text_buffer().size() - 
		math::vector::structure_cast<dim>(
			w.scroll_pos());
	
	utility::blit(
		w.text_buffer().const_view(),
		rect(
			w.scroll_pos(),
			scroll_size),
		c.view(),
		rect(
			point(1,1),
			scroll_size),
		rect(
			point(1,1),
			dim(w.size().w()-2,w.size().h()-2)
			)
		);

	blit_invalid(w,c,e);
}
