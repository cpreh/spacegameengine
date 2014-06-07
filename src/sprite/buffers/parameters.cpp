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


#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/buffers/parameters.hpp>


sge::sprite::buffers::parameters::parameters(
	sge::renderer::device::core &_device,
	sge::renderer::vertex::declaration const &_vertex_declaration
)
:
	device_(
		_device
	),
	vertex_declaration_(
		_vertex_declaration
	)
{
}

sge::renderer::device::core &
sge::sprite::buffers::parameters::device() const
{
	return device_;
}

sge::renderer::vertex::declaration const &
sge::sprite::buffers::parameters::vertex_declaration() const
{
	return vertex_declaration_;
}
