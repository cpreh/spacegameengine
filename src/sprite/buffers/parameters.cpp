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


#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/sprite/buffers/parameters.hpp>


sge::sprite::buffers::parameters::parameters(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vertex_declaration
)
:
	renderer_(
		_renderer
	),
	vertex_declaration_(
		_vertex_declaration
	)
{
}

sge::renderer::device &
sge::sprite::buffers::parameters::renderer() const
{
	return renderer_;
}

sge::renderer::vertex_declaration const &
sge::sprite::buffers::parameters::vertex_declaration() const
{
	return vertex_declaration_;
}
