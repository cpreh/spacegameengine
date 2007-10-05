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


#ifndef SGE_FONT_DRAWER_3D_HPP_INCLUDED
#define SGE_FONT_DRAWER_3D_HPP_INCLUDED

#include <vector>
#include <map>
#include "color.hpp"
#include "font_drawer.hpp"
#include "renderer.hpp"
#include "font_types.hpp"
#include "../texture/manager.hpp"
#include "../sprite/system.hpp"
#include "../sprite/sprite.hpp"

namespace sge
{

class font_drawer_3d : public font_drawer {
public:
	font_drawer_3d(renderer_ptr rend, color col = colors::white);
	void begin_rendering(size_type buffer_chars, font_dim size);
	void draw_char(font_char, font_rect, const font_color* data);
	void end_rendering();
	void set_color(color col);
private:
	renderer_ptr                                     rend;
	color                                            col;
	texture_manager                                  texman;
	typedef std::map<font_char, virtual_texture_ptr> texture_map;
	texture_map                                      textures;
	sprite_system                                    sys;
	typedef std::vector<sprite>                      sprite_vector;
	sprite_vector                                    sprites;
};

}

#endif
