/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>


sge::renderer::vertex::scoped_buffer::scoped_buffer(
	sge::renderer::context::core &_context,
	sge::renderer::vertex::buffer const &_vertex_buffer
)
:
	context_(
		_context
	),
	vertex_buffer_(
		_vertex_buffer
	)
{
	context_.activate_vertex_buffer(
		_vertex_buffer
	);
}

sge::renderer::vertex::scoped_buffer::~scoped_buffer()
{
	context_.deactivate_vertex_buffer(
		vertex_buffer_
	);
}
