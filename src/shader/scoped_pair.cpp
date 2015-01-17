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


#include <sge/shader/context.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/scoped_pair.hpp>
#include <sge/shader/parameter/planar_texture.hpp>


sge::shader::scoped_pair::scoped_pair(
	sge::renderer::context::core &_render_context,
	sge::shader::pair &_parent)
:
	parent_(
		_parent),
	scoped_vertex_program_(
		_render_context,
		parent_.loaded_vertex_program()),
	scoped_pixel_program_(
		_render_context,
		parent_.loaded_pixel_program())
{
	for(
		auto const ptr
		:
		parent_.planar_textures_
	)
		ptr->activate(
			_render_context);
}

sge::shader::scoped_pair::~scoped_pair()
{
	for(
		auto const ptr
		:
		parent_.planar_textures_
	)
		ptr->deactivate();
}
