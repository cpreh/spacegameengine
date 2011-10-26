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


#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/glew/is_supported.hpp>

sge::opengl::vf::attribute_context::attribute_context()
:
	is_native_(
		sge::opengl::glew::is_supported("GL_VERSION_2_0")
	),
	is_arb_(
		sge::opengl::glew::is_supported("GL_ARB_vertex_shader")
	),
	vertex_attrib_pointer_(
		is_native_
		?
			glVertexAttribPointer
		:
			is_arb_
			?
				glVertexAttribPointerARB
			:
				0
	),
	enable_vertex_attrib_array_(
		is_native_
		?
			glEnableVertexAttribArray
		:
			is_arb_
			?
				glEnableVertexAttribArrayARB
			:
				0
	),
	disable_vertex_attrib_array_(
		is_native_
		?
			glDisableVertexAttribArray
		:
			is_arb_
			?
				glDisableVertexAttribArrayARB
			:
				0
	)
{
}

sge::opengl::vf::attribute_context::~attribute_context()
{
}

bool
sge::opengl::vf::attribute_context::is_supported() const
{
	return
		is_native_
		|| is_arb_;
}

PFNGLVERTEXATTRIBPOINTERPROC
sge::opengl::vf::attribute_context::vertex_attrib_pointer() const
{
	return vertex_attrib_pointer_;
}

PFNGLENABLEVERTEXATTRIBARRAYPROC
sge::opengl::vf::attribute_context::enable_vertex_attrib_array() const
{
	return enable_vertex_attrib_array_;
}

PFNGLDISABLEVERTEXATTRIBARRAYPROC
sge::opengl::vf::attribute_context::disable_vertex_attrib_array() const
{
	return disable_vertex_attrib_array_;
}

sge::opengl::context::id const
sge::opengl::vf::attribute_context::static_id(
	sge::opengl::context::make_id()
);
