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


#ifndef SGE_RENDERER_SCOPED_VERTEX_LOCK_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_VERTEX_LOCK_HPP_INCLUDED

#include "vertex_buffer.hpp"
#include "vertex_view.hpp"
#include "scoped_lock_wrapper.hpp"
#include "scoped_lock.hpp"
#include "../export.hpp"

namespace sge
{
namespace renderer
{

typedef scoped_lock<
	vertex_buffer_ptr,
	vertex_view
> scoped_vertex_lock;

typedef scoped_lock<
	const_vertex_buffer_ptr,
	const_vertex_view
> const_scoped_vertex_lock;

typedef scoped_lock_wrapper<
	vertex_buffer_ptr,
	vertex_view
> scoped_vertex_lock_wrapper;

typedef scoped_lock_wrapper<
	const_vertex_buffer_ptr,
	const_vertex_view
> const_scoped_vertex_lock_wrapper;

SGE_SYMBOL scoped_vertex_lock_wrapper const
make_scoped_lock(
	vertex_buffer_ptr t,
	lock_flag_t flags,
	vertex_buffer::size_type first = 0,
	vertex_buffer::size_type count = vertex_buffer::npos);

SGE_SYMBOL const_scoped_vertex_lock_wrapper const
make_scoped_lock(
	const_vertex_buffer_ptr t,
	vertex_buffer::size_type first = 0,
	vertex_buffer::size_type count = vertex_buffer::npos);

}
}

#endif
