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


#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/sprite/render/parameters.hpp>


sge::sprite::render::parameters::parameters(
	sge::renderer::context::object &_render_context,
	sge::renderer::vertex_declaration const &_vertex_declaration
)
:
	render_context_(
		_render_context
	),
	vertex_declaration_(
		_vertex_declaration
	)
{
}

sge::renderer::context::object &
sge::sprite::render::parameters::render_context() const
{
	return
		render_context_;
}

sge::renderer::vertex_declaration const &
sge::sprite::render::parameters::vertex_declaration() const
{
	return
		vertex_declaration_;
}
