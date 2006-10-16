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


#include <algorithm>
#include <stdexcept>
#include "../system.hpp"
#include "../../renderer/vertex_format.hpp"
#include "../../renderer/lock_ptr.hpp"
#include "../../functional.hpp"

//TODO: maybe exchange dereference_binder with something of boost::lambda

namespace
{

void default_texture_not_present_handler(sge::sprite_system&, const std::string& s)
{
	throw std::runtime_error(std::string("texture \"") + s + "\" not present in sprite_system! (default handler)");
}

}

sge::sprite_system::sprite_system(const renderer_ptr rend, const handler_function handler)
 : texture_not_present_handler(handler == 0 ? default_texture_not_present_handler : handler),
   rend(rend),
   texsize(512), // TODO: let the driver determinate the best texture size
   tex_man(rend)
{
	const unsigned init_sprites = 25;
	vb = rend->create_vertex_buffer(vertex_format().add(VU_Pos).add(VU_Tex),init_sprites * detail::vertices_per_sprite, RF_WriteOnly | RF_Dynamic);
	ib = rend->create_index_buffer(init_sprites * detail::indices_per_sprite);
	free_pos.reserve(init_sprites);
	for(unsigned i = 0; i < init_sprites; ++i)
		free_pos.push_back(i * detail::vertices_per_sprite);
}

sge::vertex_buffer::size_type sge::sprite_system::free_vb_pos()
{
	if(free_pos.empty())
	{
		const unsigned grow_factor = 2;
		const vertex_buffer::size_type new_size = vb->size() * grow_factor;
		free_pos.reserve(new_size / detail::vertices_per_sprite);
		for(unsigned i = vb->size(); i < new_size; i += detail::vertices_per_sprite)
			free_pos.push_back(i);
		vb->resize(new_size);
		ib->resize(ib->size() * grow_factor);
	}
	const vertex_buffer::size_type vb_pos = free_pos.back();
	free_pos.pop_back();
	return vb_pos;
}

sge::sprite_list::iterator sge::sprite_system::attach(sprite& s)
{
	sprites.push_back(&s);
	return --sprites.end();
}

void sge::sprite_system::detach(const sprite& s)
{
	free_pos.push_back(s.vb_pos);
	sprites.erase(s.my_place);
}

bool sge::sprite_system::add_texture(const texture::const_pointer src, const texture::size_type w, const texture::size_type h, const std::string& name)
{
	if(virtual_textures.find(name) != virtual_textures.end())
		return false;

	virtual_textures[name] = tex_man.add_texture(src,w,h);
	return true;
}

bool sge::sprite_system::add_texture(const image_ptr im, const std::string& name)
{
	try
	{
		return add_texture(im->data(),im->width(),im->height(),name);
	}
	catch(const image_too_big&)
	{
		const texture::size_type max_size = rend->caps().max_tex_size;
		const unsigned factor = std::max(im->width(),im->height()) / max_size + 1;

		im->resize(im->width() / factor, im->height() / factor);
		return add_texture(im->data(),im->width(),im->height(),name);
	}
	return false;
}

void sge::sprite_system::insert_texture(const virtual_texture_ptr t, const texture::const_pointer src, const std::string& name)
{
	t->set_data(src);
	virtual_textures[name] = t;
}

bool sge::sprite_system::remove_texture(const std::string& name)
{
	virtual_texture_map::iterator it = virtual_textures.find(name);
	if(it == virtual_textures.end())
		return false;
	virtual_textures.erase(it);
	return true;
}

void sge::sprite_system::clear()
{
	virtual_textures.clear();
}

void sge::sprite_system::draw()
{
	sprites.sort(dereference_binder<const sprite*,const sprite*>(std::ptr_fun(sprite::less)));
	{
		lock_ptr<index_buffer_ptr> _lock(ib,LF_Discard);
		index_buffer::iterator it = ib->begin();
		for(sprite_list::iterator sit = sprites.begin(); sit != sprites.end(); ++sit)
			it = (*sit)->update_ib(it);
	}

	{
		lock_ptr<vertex_buffer_ptr> _lock(vb,LF_Discard);
		std::for_each(sprites.begin(),sprites.end(),std::mem_fun(&sprite::update));
	}

	set_parameters();

	unsigned first_index = 0;
	for(sprite_list::iterator it = sprites.begin(); it != sprites.end() && (*it)->visible(); )
	{
		unsigned num_objects;
		sprite_list::iterator next = first_mismatch_if(it, sprites.end(), num_objects, dereference_binder<const sprite*, const sprite*>(std::ptr_fun(sprite::equal_texture)));
		if((*it)->get_texture())
		{
			rend->set_texture(0,(*it)->get_texture());
			rend->render(vb,ib,0,vb->size(),PT_Triangle,num_objects*2,first_index);
		}
		first_index += num_objects * detail::indices_per_sprite;
		it = next;
	}
}

void sge::sprite_system::transform(const matrix_type& mat)
{
	trans = mat;
}

void sge::sprite_system::set_parameters()
{
	rend->set_bool_state(BS_EnableLighting,false);
	rend->set_transformation(trans);
	rend->projection_orthogonal();
	rend->set_filter_state(0,FARG_MinFilter,FARGV_Linear);
	rend->set_filter_state(0,FARG_MagFilter,FARGV_Linear);
}

sge::virtual_texture_ptr sge::sprite_system::vtexture(const std::string& name)
{
	if(name == no_texture)
		return virtual_texture_ptr();
	
	virtual_texture_map::const_iterator it = virtual_textures.find(name);
	if(it == virtual_textures.end())
	{
		texture_not_present_handler(*this,name);
		it = virtual_textures.find(name);
		if(it == virtual_textures.end())
			throw std::logic_error(std::string("texture_not_present_handler in sprite_system failed for texture \"") += name + "\"!");
	}
	return it->second;
}

sge::renderer_ptr sge::sprite_system::get_renderer() const
{
	return rend;
}

const char* const sge::sprite_system::no_texture = "";
