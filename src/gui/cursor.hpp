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


#ifndef SGE_GUI_CURSOR_HPP_INCLUDED
#define SGE_GUI_CURSOR_HPP_INCLUDED

#include <string>
#include <boost/shared_ptr.hpp>

#include "canvas.hpp"
#include "types.hpp"

namespace sge {
namespace gui {

struct cursor_base {
	virtual ~cursor_base() {}
	virtual void blit(canvas &dest, point position) const = 0;
};

struct normal_cursor : public cursor_base {
	canvas bitmap;
	point  hotspot;

	void blit(canvas &dest, point position) const;
};

typedef boost::shared_ptr<cursor_base> cursor_ptr;

namespace cursor {
	inline cursor_ptr from_canvas(const canvas &image, point hotspot) {
		normal_cursor *nc;
		cursor_ptr cp(nc = new normal_cursor());
		nc->bitmap  = image;
		nc->hotspot = hotspot;
		return cp;
	}

	inline cursor_ptr from_bitmap(const std::string &image, point hotspot) {
		return from_canvas(canvas::from_image(image), hotspot);
	}
}

}
}

#endif // SGE_GUI_CURSOR_HPP_INCLUDED
