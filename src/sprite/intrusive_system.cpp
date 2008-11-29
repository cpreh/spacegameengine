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
#include <sge/sprite/detail/render_states.hpp>
#include <sge/sprite/detail/intrusive_compare.hpp>
#include <sge/sprite/detail/fill_geometry.hpp>
#include <sge/sprite/detail/render.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <boost/foreach.hpp>

sge::sprite::intrusive_system::intrusive_system(
	renderer::device_ptr const rend)
:
	system_base(rend)
{}

void sge::sprite::intrusive_system::render()
{
	matrices();

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

	renderer::vertex_buffer_ptr const vb(
		get_vertex_buffer());
	
	renderer::index_buffer_ptr const ib(
		get_index_buffer());

	fill_geometry(
		sprites.begin(),
		sprites.end(),
		get_vertex_buffer(),
		get_index_buffer());

	renderer::device_ptr const rend(
		get_renderer());

	sprite::render(
		sprites.begin(),
		sprites.end(),
		tex_equal_visible,
		rend,
		vb,
		ib);
}

void sge::sprite::intrusive_system::add(
	intrusive_object &obj,
	intrusive_object::order_type const order)
{
	sprite_levels[order].push_back(obj);
}
