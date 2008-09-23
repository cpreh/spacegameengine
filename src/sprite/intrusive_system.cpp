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
#include <sge/sprite/helper.hpp>
#include <sge/sprite/intrusive_compare.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/algorithm.hpp>
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
		renderer::state::list
			(renderer::state::bool_::enable_lighting = false)
			(renderer::state::bool_::enable_alpha_blending = true)
			(renderer::state::source_blend_func::src_alpha)
			(renderer::state::dest_blend_func::inv_src_alpha)
			(renderer::state::cull_mode::off)
			(renderer::state::depth_func::off)
			(renderer::state::stencil_func::off)
			(renderer::state::draw_mode::fill)
	);


	BOOST_FOREACH(sprite_level_map::value_type const &v, sprite_levels)
		render(*v.second);
}

void sge::sprite::intrusive_system::render(
	sprite_list const &sprites)
{
	allocate_buffers(sprites.size());

	{
		renderer::scoped_index_lock const iblock(
			renderer::make_scoped_lock(
				get_index_buffer(),
				renderer::lock_flags::writeonly));

		renderer::scoped_vertex_lock const vblock(
			renderer::make_scoped_lock(
				get_vertex_buffer(),
				renderer::lock_flags::writeonly));

		index_view const indices(boost::get<index_view>(iblock.value()));
		renderer::vertex_view const vertices(vblock.value());

		index_view::iterator ib_it = indices.begin();
		renderer::vertex_view::iterator vb_it = vertices.begin();

		BOOST_FOREACH(intrusive_object const &spr, sprites)
		{
			if(!spr.visible())
				continue;

			ib_it = fill_indices(ib_it, static_cast<index_view::value_type>(vb_it - vertices.begin()));

			if(math::almost_zero(spr.rotation()))
				fill_position(vb_it, spr.get_rect(), spr.z());
			else
				fill_position_rotated(vb_it, spr.get_rect(), spr.rotation(), spr.rotation_center(), spr.z());

			if(const texture::part_ptr tex = spr.get_texture())
				fill_tex_coordinates(vb_it, tex->area_texc(spr.repeat()));

			vb_it = fill_color(vb_it, spr.get_color());
		}
	}

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
