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


#include <sge/renderer/index_buffer_util.hpp>

sge::renderer::index_buffer_ptr const
sge::renderer::resize(
	index_buffer_ptr const ib,
	device_ptr const rend,
	index_buffer::size_type const newsize)
{
	// FIXME
	return rend->create_index_buffer(
		index_buffer::const_view_type(
			const_index_view_16(
			0,
			newsize)));
}
