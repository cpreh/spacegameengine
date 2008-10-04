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

#include "../export.hpp"
#include "../renderer/any_color.hpp"
#include "../renderer/colors.hpp"
#include "../renderer/device.hpp"
#include "../texture/manager.hpp"
#include "../texture/part.hpp"
#include "../sprite/system.hpp"
#include "../sprite/object.hpp"
#include "drawer.hpp"
#include "types.hpp"
#include <map>

namespace sge
{

namespace font
{

class SGE_CLASS_SYMBOL drawer_3d : public drawer {
public:
	SGE_SYMBOL drawer_3d(
		renderer::device_ptr rend,
		renderer::any_color const &col = renderer::colors::white());
	SGE_SYMBOL void begin_rendering(
		size_type buffer_chars,
		pos const &start,
		dim size);
	SGE_SYMBOL void draw_char(
		char_type,
		pos const &,
		const_image_view const &data);
	SGE_SYMBOL void end_rendering();
	SGE_SYMBOL void set_color(
		renderer::any_color const &col);
private:
	renderer::device_ptr                             rend;
	renderer::any_color                              col;
	texture::manager                                 texman;
	typedef std::map<char_type, texture::part_ptr>   texture_map;
	texture_map                                      textures;
	sprite::system                                   sys;
	sprite::system::container                        sprites;
};

}
}

#endif
