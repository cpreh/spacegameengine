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



#ifndef SGE_FONT_DRAWER_3D_HPP_INCLUDED
#define SGE_FONT_DRAWER_3D_HPP_INCLUDED

#include <sge/font/drawer.hpp>
#include <sge/font/pos.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/image_view.hpp>
#include <sge/renderer/any_color.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/container.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/export.hpp>
#include <map>

namespace sge
{

namespace font
{

class SGE_CLASS_SYMBOL drawer_3d : public drawer {
public:
	SGE_SYMBOL drawer_3d(
		renderer::device_ptr rend,
		renderer::any_color const &col);
	SGE_SYMBOL ~drawer_3d();

	SGE_SYMBOL void begin_rendering(
		size_type buffer_chars,
		pos const &start,
		dim size);
	SGE_SYMBOL void draw_char(
		char_type,
		pos const &,
		const_image_view const &data);
	SGE_SYMBOL void end_rendering();
	SGE_SYMBOL void color(
		renderer::any_color const &col);
private:
	texture::const_part_ptr const
	cached_texture(
		char_type,
		const_image_view const &);

	renderer::device_ptr            rend;
	renderer::any_color             col;
	texture::manager                texman;
	typedef std::map<
		char_type,
		texture::const_part_ptr
	>                               texture_map;
	texture_map                     textures;
	sprite::system                  sys;
	sprite::container               sprites;
};

}
}

#endif
