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


#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/detail/instantiate_scoped_lock.hpp>

sge::renderer::scoped_vertex_lock_wrapper const
sge::renderer::make_scoped_lock(
	vertex_buffer_ptr const t,
	lock_flag_t const flags,
	vertex_buffer::size_type const first,
	vertex_buffer::size_type const count)
{
	return scoped_vertex_lock_wrapper(
		t,
		t->lock(
			flags,
			first,
			count));
}

sge::renderer::const_scoped_vertex_lock_wrapper const
sge::renderer::make_scoped_lock(
	const_vertex_buffer_ptr const t,
	vertex_buffer::size_type const first,
	vertex_buffer::size_type const count)
{
	return const_scoped_vertex_lock_wrapper(
		t,
		t->lock(
			first,
			count));
}

SGE_RENDERER_INSTANTIATE_SCOPED_LOCK(
	sge::renderer::vertex_buffer_ptr,
	sge::renderer::vertex_buffer::view_type)

SGE_RENDERER_INSTANTIATE_SCOPED_LOCK(
	sge::renderer::const_vertex_buffer_ptr,
	sge::renderer::vertex_buffer::const_view_type)
