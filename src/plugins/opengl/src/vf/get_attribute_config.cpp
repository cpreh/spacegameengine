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


#include <sge/opengl/vf/attribute_config_fwd.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/vf/get_attribute_config.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/text.hpp>


sge::opengl::vf::attribute_config const &
sge::opengl::vf::get_attribute_config(
	sge::opengl::vf::attribute_context const &_context
)
{
	return
		fcppt::optional::to_exception(
			_context.config(),
			[]{
				return
					sge::renderer::unsupported(
						FCPPT_TEXT("glVertexAttribPointer"),
						FCPPT_TEXT("GL_VERSION_2_0"),
						FCPPT_TEXT("GL_ARB_vertex_shader")
					);
			}
		);
}
