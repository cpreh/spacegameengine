/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/vertex/buffer_fwd.hpp>
#include <sge/opengl/vertex/context.hpp>
#include <sge/opengl/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/container/index_map_impl.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::vertex::context::context()
:
	sge::opengl::context::base(),
	last_declaration_(),
	last_buffers_()
{
}

sge::opengl::vertex::context::~context()
{
}

void
sge::opengl::vertex::context::vertex_buffer(
	sge::renderer::vf::dynamic::part_index const _index,
	optional_buffer const _buffer
)
{
	last_buffers_[
		_index.get()
	] =
		_buffer;
}

sge::opengl::vertex::context::optional_buffer
sge::opengl::vertex::context::vertex_buffer(
	sge::renderer::vf::dynamic::part_index const _index
) const
{
	return
		last_buffers_[
			_index.get()
		];
}

void
sge::opengl::vertex::context::vertex_declaration(
	optional_declaration const _declaration
)
{
	last_declaration_ =
		_declaration;
}

sge::opengl::vertex::context::optional_declaration
sge::opengl::vertex::context::vertex_declaration() const
{
	return
		last_declaration_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::vertex::context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
