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


#include <sge/sprite/intrusive_system.hpp>
#include <sge/sprite/intrusive_compare.hpp>
#include <sge/sprite/render_states.hpp>
#include <sge/sprite/fill_geometry.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/texture/part.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/algorithm/first_mismatch.hpp>
#include <boost/foreach.hpp>

sge::sprite::intrusive_system::intrusive_system(
	renderer::device_ptr const rend)
: system_base(rend)
{}

void sge::sprite::intrusive_system::render()
{
	set_matrices();

	renderer::device_ptr const rend(
		get_renderer());

	renderer::state::scoped const state_(
		rend,
		render_states()
	);

	BOOST_FOREACH(sprite_level_map::value_type const &v, sprite_levels)
		render(*v.second);
}

void sge::sprite::intrusive_system::render(
	sprite_list const &sprites)
{
	allocate_buffers(sprites.size());

	fill_geometry(
		sprites.begin(),
		sprites.end(),
		get_vertex_buffer(),
		get_index_buffer());

	renderer::device_ptr const rend(
		get_renderer());

	unsigned first_index = 0;
	
	sprite_list::const_iterator const end(sprites.end());

	for(sprite_list::const_iterator cur = sprites.begin(); cur != end; )
	{
		for(; cur != sprites.end() && !cur->visible(); ++cur) ;

		if(cur == sprites.end())
			break;

		unsigned num_objects;
		sprite_list::const_iterator const next = first_mismatch_if(cur, end, num_objects, tex_equal_visible);

		const texture::part_ptr vtex = cur->get_texture();
		rend->set_texture(vtex ? vtex->my_texture() : renderer::device::no_texture);
		
		rend->render(
			get_vertex_buffer(),
			get_index_buffer(),
			first_index / detail::indices_per_sprite * detail::vertices_per_sprite,
			num_objects * detail::vertices_per_sprite,
			renderer::indexed_primitive_type::triangle,
			num_objects * detail::indices_per_sprite / 3,
			first_index);

		first_index += num_objects * detail::indices_per_sprite;
		cur = next;
	}

	rend->set_texture(renderer::device::no_texture);
}

void sge::sprite::intrusive_system::add(
	intrusive_object &obj,
	intrusive_object::order_type const order)
{
	sprite_levels[order].push_back(obj);
}
