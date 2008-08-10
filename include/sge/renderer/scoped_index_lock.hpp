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


#ifndef SGE_RENDERER_SCOPED_INDEX_LOCK_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_INDEX_LOCK_HPP_INCLUDED

#include "index_buffer.hpp"
#include "index_view.hpp"
#include "scoped_lock_wrapper.hpp"
#include "scoped_lock.hpp"

namespace sge
{
namespace renderer
{

typedef scoped_lock<
	index_buffer_ptr,
	dynamic_index_view
> scoped_index_lock;

typedef scoped_lock<
	const_index_buffer_ptr,
	const_dynamic_index_view
> const_scoped_index_lock;

typedef scoped_lock_wrapper<
	index_buffer_ptr,
	dynamic_index_view
> scoped_index_lock_wrapper;

typedef scoped_lock_wrapper<
	const_index_buffer_ptr,
	const_dynamic_index_view
> const_scoped_index_lock_wrapper;

scoped_index_lock_wrapper const
make_scoped_lock(
	index_buffer_ptr t,
	lock_flag_t flags,
	index_buffer::size_type first = 0,
	index_buffer::size_type count = index_buffer::npos);

const_scoped_index_lock_wrapper const
make_scoped_lock(
	const_index_buffer_ptr t,
	index_buffer::size_type first = 0,
	index_buffer::size_type count = index_buffer::npos);

}
}

#endif
