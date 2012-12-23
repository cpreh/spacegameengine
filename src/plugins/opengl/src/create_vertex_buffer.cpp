/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/opengl/create_vertex_buffer.hpp>
#include <sge/opengl/vertex_buffer.hpp>
#include <sge/opengl/vertex_declaration.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::renderer::vertex::buffer_unique_ptr
sge::opengl::create_vertex_buffer(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::vertex::buffer_parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sge::opengl::vertex_buffer
		>(
			_system_context,
			_parameters.part(),
			dynamic_cast<
				sge::opengl::vertex_declaration const &
			>(
				_parameters.declaration()
			).format_part(
				_parameters.part()
			),
			_parameters.count(),
			_parameters.flags()
		);
}
