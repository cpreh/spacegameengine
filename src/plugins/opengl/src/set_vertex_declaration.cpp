/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/set_vertex_declaration.hpp>
#include <sge/opengl/vertex_context.hpp>
#include <sge/opengl/vertex_declaration.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/cast/static_downcast.hpp>


void
sge::opengl::set_vertex_declaration(
	sge::opengl::context::object &_context,
	sge::renderer::vertex::const_optional_declaration_ref const &_opt_declaration
)
{
	sge::opengl::context::use<
		sge::opengl::vertex_context
	>(
		_context
	).vertex_declaration(
		fcppt::optional_bind_construct(
			_opt_declaration,
			[](
				sge::renderer::vertex::declaration const &_declaration
			)
			-> sge::opengl::vertex_declaration const &
			{
				return
					fcppt::cast::static_downcast<
						sge::opengl::vertex_declaration const &
					>(
						_declaration
					);
			}
		)
	);
}
