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


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::vf::attribute_context::attribute_context()
:
	sge::opengl::context::system::base(),
	is_native_(
		GLEW_VERSION_2_0
	),
	is_arb_(
		GLEW_ARB_vertex_shader
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
				fcppt::null_ptr()
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
				fcppt::null_ptr()
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
				fcppt::null_ptr()
	)
{
}

FCPPT_PP_POP_WARNING

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

sge::opengl::vf::attribute_context::gl_vertex_attrib_pointer
sge::opengl::vf::attribute_context::vertex_attrib_pointer() const
{
	return vertex_attrib_pointer_;
}

sge::opengl::vf::attribute_context::gl_enable_vertex_attrib_array
sge::opengl::vf::attribute_context::enable_vertex_attrib_array() const
{
	return enable_vertex_attrib_array_;
}

sge::opengl::vf::attribute_context::gl_disable_vertex_attrib_array
sge::opengl::vf::attribute_context::disable_vertex_attrib_array() const
{
	return disable_vertex_attrib_array_;
}

sge::opengl::context::system::id const
sge::opengl::vf::attribute_context::static_id(
	sge::opengl::context::system::make_id()
);
