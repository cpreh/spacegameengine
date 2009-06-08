/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/impl/const_scoped_buffer_lock_impl.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/export.hpp>

template SGE_SYMBOL class
sge::renderer::detail::const_scoped_buffer_lock<
	sge::renderer::const_vertex_buffer_ptr,
	sge::renderer::vf::const_dynamic_view
>;
