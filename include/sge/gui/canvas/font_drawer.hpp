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


#ifndef SGE_GUI_CANVAS_FONT_DRAWER_HPP_INCLUDED
#define SGE_GUI_CANVAS_FONT_DRAWER_HPP_INCLUDED

#include <sge/gui/canvas/optional_character_pos.hpp>
#include <sge/gui/image_view.hpp>
#include <sge/gui/color.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/export.hpp>
#include <sge/font/drawer.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/char_type.hpp>

namespace sge
{
namespace gui
{
namespace canvas
{
class SGE_CLASS_SYMBOL font_drawer : public font::drawer
{
public:
	SGE_GUI_SYMBOL font_drawer(
		image_view &,
		color,
		optional_character_pos const & = optional_character_pos(),
		point * = 0);

	// NOTE: this is font::drawer::size_type, _not_ font::size_type!
	SGE_GUI_SYMBOL void begin_rendering(
		size_type,
		font::pos const &,
		font::dim const &);

	SGE_GUI_SYMBOL void draw_char(
		fcppt::char_type,
		font::pos const &c,
		font::const_image_view const &);

	SGE_GUI_SYMBOL void end_rendering();
private:
	image_view &texture_;
	color const c;
	unsigned counter;
	optional_character_pos character_pos;
	point *p;
};
}
}
}

#endif
