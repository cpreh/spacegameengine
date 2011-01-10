/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../actor_parameters.hpp"

sge::opengl::vf::actor_parameters::actor_parameters(
	sge::renderer::size_type const _stride,
	sge::renderer::size_type const _offset,
	opengl::context::object &_context
)
:
	stride_(_stride),
	offset_(_offset),
	context_(_context)
{}

sge::renderer::size_type
sge::opengl::vf::actor_parameters::stride() const
{
	return stride_;
}

sge::renderer::size_type
sge::opengl::vf::actor_parameters::offset() const
{
	return offset_;
}

sge::opengl::context::object &
sge::opengl::vf::actor_parameters::context() const
{
	return context_;
}
