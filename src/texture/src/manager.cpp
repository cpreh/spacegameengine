/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../manager.hpp"

sge::texture_manager::texture_manager(const renderer_ptr rend, const fragmented_texture* const nproto)
 : rend(rend),
   _prototype(nproto)
{}

sge::virtual_texture_ptr sge::texture_manager::add_texture(const texture::const_pointer src, const texture::size_type w, const texture::size_type h)
{
	for(fragmented_texture_list::iterator it = fragmented_textures.begin(); it != fragmented_textures.end(); ++it)
		if(virtual_texture_ptr p = it->consume_fragments(w,h))
		{
			p->set_data(src);
			return p;
		}

	fragmented_textures.push_back(_prototype->clone());
	if(virtual_texture_ptr p = fragmented_textures.back().consume_fragments(w,h))
	{
		p->set_data(src);
		return p;
	}
	throw image_too_big();
}

sge::virtual_texture_ptr sge::texture_manager::add_texture(const image_ptr im)
{
	try
	{
		return add_texture(im->data(),im->width(),im->height());
	}
	catch(const texture_manager::image_too_big&)
	{
		const texture::size_type max_size = rend->caps().max_tex_size;
		const unsigned factor = 1 + std::max(im->width(),im->height()) / unsigned(max_size);
		im->resample(im->width() / factor, im->height() / factor);
		return add_texture(im->data(),im->width(),im->height());
	}
}

sge::renderer_ptr sge::texture_manager::get_renderer() const
{
	return rend;
}

void sge::texture_manager::prototype(fragmented_texture* const p)
{
	_prototype.reset(p);
}
