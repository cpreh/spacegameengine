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


#include "../manager.hpp"
#include "../static_texture.hpp"

sge::texture_manager::texture_manager(const renderer_ptr rend, const onalloc_function& onalloc_)
 : rend(rend),
   onalloc_(onalloc_)
{}

const sge::virtual_texture_ptr sge::texture_manager::add_texture(const texture::const_pointer src, const texture::size_type w, const texture::size_type h)
{
	for(fragmented_texture_list::iterator it = fragmented_textures.begin(); it != fragmented_textures.end(); ++it)
		if(const virtual_texture_ptr p = init_texture(*it, src, w, h))
			return p;

	fragmented_textures.push_back(onalloc_());

	if(const virtual_texture_ptr p = init_texture(fragmented_textures.back(), src, w, h))
		return p;
	throw image_too_big();
}

const sge::virtual_texture_ptr sge::texture_manager::init_texture(fragmented_texture& tex, const texture::const_pointer src, const texture::size_type w, const texture::size_type h) const
{
	const virtual_texture_ptr p = tex.consume_fragments(w, h);
	if(p)
		p->set_data(src);
	return p;
}

const sge::virtual_texture_ptr sge::texture_manager::add_texture(const texture_ptr tex)
{
	fragmented_textures.push_back(new static_texture(tex));
	return fragmented_textures.back().consume_fragments(tex->width(), tex->height());
}

const sge::renderer_ptr sge::texture_manager::get_renderer() const
{
	return rend;
}

void sge::texture_manager::onalloc(const onalloc_function& fun)
{
	onalloc_ = fun;
}

sge::texture_manager::image_too_big::image_too_big()
: exception("texture_manager::add_texture() image too big!")
{}
