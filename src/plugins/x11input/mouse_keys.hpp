/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_MOUSE_KEYS_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_KEYS_HPP_INCLUDED

#include <sge/input/key_type.hpp>

namespace sge
{
namespace x11input
{

extern input::key_type const
	mouse_x,
	mouse_y,
	undefined_mouse_key,
	mouse_l,
	mouse_r,
	mouse_m;

}
}

#endif
