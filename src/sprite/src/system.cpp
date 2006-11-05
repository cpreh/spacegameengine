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
#include "../sprite.hpp"
#include "../../renderer/transform.hpp"

//TODO: maybe exchange dereference_binder with something of boost::lambda

sge::sprite_system::sprite_system(const renderer_ptr rend, const handler_function handler)
 : texture_map(rend,handler),
   rend(rend),
   drawer(rend)
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

void sge::sprite_system::draw(const vector2 trans)
{
	sprite_list to_draw;
	for(sprite_list::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
		if(intersects((*it)->get_rect() - trans, rect(0,0,1,1)))
				to_draw.push_back(*it);

	to_draw.sort(dereference_binder<const sprite*,const sprite*>(std::ptr_fun(sprite::less)));
	{
		lock_ptr<index_buffer_ptr> _lock(ib,LF_Discard);
		index_buffer::iterator it = ib->begin();
		for(sprite_list::iterator sit = to_draw.begin(); sit != to_draw.end(); ++sit)
			it = (*sit)->update_ib(it);
	}

	{
		lock_ptr<vertex_buffer_ptr> _lock(vb,LF_Discard);
		std::for_each(to_draw.begin(), to_draw.end(),std::mem_fun(&sprite::update));
	}

	rend->set_transformation(matrix_translation(trans_2d_to_3d(trans)));

	drawer.draw(to_draw, vb, ib);
}

void sge::sprite_system::set_parameters()
{
	drawer.set_parameters();
}

sge::renderer_ptr sge::sprite_system::get_renderer() const
{
	return rend;
}

