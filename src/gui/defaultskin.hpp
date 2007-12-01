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


#ifndef SGE_GUI_DEFAULTSKIN_HPP_INCLUDED
#define SGE_GUI_DEFAULTSKIN_HPP_INCLUDED

#include "skin.hpp"

namespace sge {
namespace gui {

struct defaultskin : public skin {
protected:
	defaultskin();

public:
	~defaultskin();

	rect adjust_to_border(widget*, border_style::type, rect) const;
	void draw_border     (widget*, border_style::type,      focus_modifier::type, rect, canvas &) const;
	void draw_background (widget*, border_style::type,      focus_modifier::type, rect, canvas &) const;
	void draw_icon       (widget*, stock_icon::type,       focus_modifier::type, rect, canvas &) const;
	dim2 icon_size       () const;

public:
	static skin_ptr get();
	static const unsigned icons[][11];
};

}
}

#endif // SGE_GUI_DEFAULTSKIN_HPP_INCLUDED
