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
#include <functional>
#include <boost/lambda/bind.hpp>
#include "../system.hpp"
#include "../sprite.hpp"
#include "../../renderer/vertex_format.hpp"
#include "../../renderer/lock_ptr.hpp"
#include "../../renderer/transform.hpp"

#include "../../texture/no_fragmented_texture.hpp" // TODO: remove later

const unsigned init_sprites = 25;

// convenience function, remove later
sge::sprite_system::sprite_system(const renderer_ptr rend, const texture_map::handler_function handler, const stage_type _max_tex)
 : default_transformable(rend, matrix_2d_to_3d(), math::matrix_orthogonal_xy()),
   tex_map(new texture_map(rend, new no_fragmented_texture(rend), handler)),
   rend(rend),
   _max_tex(_max_tex)
{
	init();
}

sge::sprite_system::sprite_system(const renderer_ptr rend, const texture_map_ptr tex_map, const stage_type _max_tex)
 : default_transformable(rend, matrix_2d_to_3d(), math::matrix_orthogonal_xy()),
   tex_map(tex_map),
   rend(rend),
   _max_tex(_max_tex)
{
	init();
}

void sge::sprite_system::init()
{
	vb = rend->create_vertex_buffer(vertex_format().add(vertex_usage::pos).add(vertex_usage::diffuse).add(vertex_usage::tex, _max_tex),
	                                init_sprites * detail::vertices_per_sprite,
	                                resource_flags::write_only | resource_flags::dynamic);
	ib = rend->create_index_buffer(init_sprites * detail::indices_per_sprite);
	_sprite_vb_buf.resize(vb->get_vertex_format().stride() * detail::vertices_per_sprite);
	free_pos.reserve(init_sprites);
	for(unsigned i = 0; i < init_sprites; ++i)
		free_pos.push_back(i * detail::vertices_per_sprite);
}

sge::texture_map_ptr sge::sprite_system::get_texture_map() const
{
	return tex_map;
}

sge::vertex_buffer::size_type sge::sprite_system::free_vb_pos()
{
	if(free_pos.empty())
	{
		const free_pos_vector::size_type grow_factor = 2;
		const vertex_buffer::size_type new_size = vb->size() * grow_factor;
		free_pos.reserve(new_size / detail::vertices_per_sprite);
		for(free_pos_vector::size_type i = vb->size(); i < new_size; i += detail::vertices_per_sprite)
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

void sge::sprite_system::render()
{
	sprites.sort(boost::lambda::bind(&sprite::less, *boost::lambda::_1, *boost::lambda::_2));
	{
		lock_ptr<index_buffer_ptr> _lock(ib);
		index_buffer::iterator it = ib->begin();
		for(sprite_list::iterator sit = sprites.begin(); sit != sprites.end(); ++sit)
			it = (*sit)->update_ib(it);
	}

	{
		lock_ptr<vertex_buffer_ptr> _lock(vb);
		std::for_each(sprites.begin(), sprites.end(), std::mem_fun(&sprite::update));
	}

	set_parameters();
	unsigned first_index = 0;
	for(sprite_list::const_iterator it = sprites.begin(); it != sprites.end(); )
	{
		if(!(*it)->visible())
			break;

		unsigned num_objects;
		const sprite_list::const_iterator next = first_mismatch_if(it, sprite_list::const_iterator(sprites.end()), num_objects, boost::lambda::bind(&sprite::equal, *boost::lambda::_1, *boost::lambda::_2));

		for(stage_type stage = 0; stage < max_tex_level(); ++stage)
			rend->set_texture((*it)->get_texture(stage), stage);

		rend->render(vb, ib, 0, vb->size(), indexed_primitive_type::triangle, num_objects*2, first_index);
		first_index += num_objects * detail::indices_per_sprite;
		it = next;
	}

	for(stage_type stage = 1; stage < max_tex_level(); ++stage)
		rend->set_texture(texture_ptr(), stage);
}

void sge::sprite_system::set_parameters()
{
	set_matrices();
	rend->set_bool_state(bool_state::enable_lighting, false);
	rend->set_bool_state(bool_state::enable_alpha_blending, true);
}

sge::renderer_ptr sge::sprite_system::get_renderer() const
{
	return rend;
}

sge::stage_type sge::sprite_system::max_tex_level() const
{
	return _max_tex;
}
