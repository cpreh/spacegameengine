/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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


#ifndef SGE_GUI_SKIN_HPP_INCLUDED
#define SGE_GUI_SKIN_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include "types.hpp"

namespace sge {
namespace gui {

class canvas;
class widget;

struct skin {
	skin() {}
	virtual ~skin() {}

	struct stock_icon { enum type {
		none, empty,

		left     , leftmost     , left_double , leftmost_double ,
		right    , rightmost    , right_double, rightmost_double,
		up       , upmost       , up_double   , upmost_double   ,
		down     , downmost     , down_double , downmost_double ,
		updown   , updownmost   ,
		leftright, leftrightmost,
		fourway,

		ellipsis,
		minimize, restore, maximize, close,

		// aliases
		downup = updown,
		downupmost = updownmost,
		rightleft = leftright,
		rightleftmost = leftrightmost,

		num_icons
	}; };

	struct border_style { enum type {
		none,
		frame,
		button,
		iconbutton
	}; };

	struct focus_modifier { enum type {
		none         = 0,
		hover        = 1,
		active       = 2,
		hover_active = hover | active
	}; };

	struct scroll_direction { enum type {
		horizontal,
		vertical,

		// aliases
		leftright = horizontal,
		rightleft = horizontal,
		updown    = vertical,
		downup    = vertical
	}; };

	// returns the boundary rect to use if the given rect should remain as view port after decoration
	virtual rect adjust_to_border(widget*, border_style::type, rect) const = 0;

	// draw a border of the given type
	virtual void draw_border     (widget*, border_style::type, focus_modifier::type, rect, canvas &) const = 0;

	// draw a widgets background
	virtual void draw_background (widget*, border_style::type, focus_modifier::type, rect, canvas &) const = 0;

	// draws icon centered
	virtual void draw_icon       (widget*, stock_icon::type,  focus_modifier::type, rect, canvas &) const = 0;

	// returns icon size
	virtual dim2 icon_size       () const = 0;
};

typedef boost::shared_ptr<skin> skin_ptr;

}
}

#endif // SGE_GUI_SKIN_HPP_INCLUDED
