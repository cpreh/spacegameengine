/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/vertex_buffer_fwd.hpp>
#include <sge/opengl/vertex_context.hpp>
#include <sge/opengl/vertex_declaration_fwd.hpp>
#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <sge/opengl/context/device/make_id.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/container/index_map_impl.hpp>


sge::opengl::vertex_context::vertex_context()
:
	sge::opengl::context::device::base(),
	last_declaration_(
		nullptr
	),
	last_buffers_()
{
}

sge::opengl::vertex_context::~vertex_context()
{
}

sge::opengl::vertex_buffer const *
sge::opengl::vertex_context::vertex_buffer(
	sge::renderer::vf::dynamic::part_index const _index
) const
{
	return
		last_buffers_[
			_index.get()
		];
}

void
sge::opengl::vertex_context::vertex_buffer(
	sge::renderer::vf::dynamic::part_index const _index,
	sge::opengl::vertex_buffer const *const _buffer
)
{
	last_buffers_[
		_index.get()
	] =
		_buffer;
}

void
sge::opengl::vertex_context::vertex_declaration(
	sge::opengl::vertex_declaration const *const _declaration
)
{
	last_declaration_ = _declaration;
}

sge::opengl::vertex_declaration const *
sge::opengl::vertex_context::vertex_declaration() const
{
	return
		last_declaration_;
}

sge::opengl::context::device::id const
sge::opengl::vertex_context::static_id(
	sge::opengl::context::device::make_id()
);
