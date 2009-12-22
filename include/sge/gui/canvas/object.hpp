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


#ifndef SGE_GUI_CANVAS_OBJECT_HPP_INCLUDED
#define SGE_GUI_CANVAS_OBJECT_HPP_INCLUDED

#include <sge/gui/canvas/rect_type.hpp>
#include <sge/gui/canvas/line_type.hpp>
#include <sge/gui/canvas/strip_type.hpp>
#include <sge/gui/canvas/optional_character_pos.hpp>
#include <sge/gui/image.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/rect.hpp>
#include <sge/gui/image_view.hpp>
#include <sge/gui/color.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/font_info.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/align_v.hpp>
#include <sge/font/flags.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional.hpp>

#include <vector>

namespace sge
{
namespace gui
{
namespace canvas
{
class object
{
	FCPPT_NONCOPYABLE(object)
	public:
	SGE_GUI_SYMBOL explicit object(image &);
	SGE_GUI_SYMBOL ~object();

	SGE_GUI_SYMBOL dim const size() const;
	SGE_GUI_SYMBOL rect const area() const;
	SGE_GUI_SYMBOL image_view &view();
	SGE_GUI_SYMBOL const_image_view const view() const;

	SGE_GUI_SYMBOL void draw_rect(
		rect const &,
		color,
		rect_type::type);

	SGE_GUI_SYMBOL void draw_text(
		font_info const &,
		fcppt::string const &,
		point const &,
		dim const &max_size,
		font::align_h::type,
		font::align_v::type,
		font::flag_t = font::flags::default_,
		optional_character_pos = optional_character_pos(),
		point * = 0);

	SGE_GUI_SYMBOL void draw_line(
		point const &,
		point const &,
		color,
		line_type::type type = line_type::solid);

	typedef std::vector<point> point_container;

	SGE_GUI_SYMBOL void draw_line_strip(
		point_container const &,
		color,
		line_type::type = line_type::solid,
		strip_type::type = strip_type::open);

	SGE_GUI_SYMBOL void draw_pixel(point const &,color);
	private:
	image &texture_;
	image_view view_;
};
}
}
}

#endif
