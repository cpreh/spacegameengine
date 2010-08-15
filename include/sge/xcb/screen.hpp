/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_XCB_SCREEN_HPP_INCLUDED
#define SGE_XCB_SCREEN_HPP_INCLUDED

#include <sge/xcb/screen_fwd.hpp>
#include <sge/xcb/window/id_num.hpp>
#include <sge/xcb/visual/id_num.hpp>
#include <sge/xcb/symbol.hpp>
#include <xcb/xcb.h>

namespace sge
{
namespace xcb
{

class screen
{
public:
	SGE_XCB_SYMBOL
	explicit screen(
		xcb_screen_t *
	);

	SGE_XCB_SYMBOL
	visual::id_num const
	root_visual() const;

	SGE_XCB_SYMBOL
	window::id_num const
	root_window() const;
private:
	xcb_screen_t *screen_;
};

}
}

#endif
