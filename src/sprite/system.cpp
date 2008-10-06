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


#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/compare.hpp>
#include <sge/sprite/render_states.hpp>
#include <sge/sprite/fill_geometry.hpp>
#include <sge/sprite/render.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <iterator>

sge::sprite::system::system(
	renderer::device_ptr const rend)
 : system_base(rend)
 {}

void sge::sprite::system::render(
	container::iterator const begin,
	container::iterator const end,
	sort_method const &sort_fun)
{
	if(begin == end)
		return;
	object *const beg(&*begin);
	render(
		beg,
		beg + std::distance(begin, end),
		sort_fun);
}

void sge::sprite::system::render(
	object *const beg,
	object *const end,
	sort_method const &sort_fun)
{
	sort_fun(beg, end, less);
	
	allocate_buffers(std::distance(beg, end));

	renderer::vertex_buffer_ptr const vb(
		get_vertex_buffer());
	
	renderer::index_buffer_ptr const ib(
		get_index_buffer());

	fill_geometry(
		beg,
		end,
		vb,
		ib);

	set_matrices();

	renderer::device_ptr const rend(
		get_renderer());

	renderer::state::scoped const state_(
		rend,
		render_states()
	);

	sprite::render(
		beg,
		end,
		equal,
		rend,
		vb,
		ib);
}

void sge::sprite::system::render(
	object o)
{
	render(&o, &o+1);
}

sge::sprite::system::sort_method const
sge::sprite::system::default_sort(
	std::stable_sort<
		sge::sprite::object *,
		bool (*)(sge::sprite::object const &, sge::sprite::object const &)
	>
);
