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


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/vf/attribute_config.hpp>
#include <sge/opengl/vf/attribute_context_fwd.hpp>
#include <sge/opengl/vf/disable_vertex_attrib_array.hpp>
#include <sge/opengl/vf/get_attribute_config.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::vf::disable_vertex_attrib_array(
	sge::opengl::vf::attribute_context const &_context,
	GLuint const _index
)
{
	sge::opengl::call_fun_ref(
		sge::opengl::vf::get_attribute_config(
			_context
		).disable_vertex_attrib_array(),
		_index
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Disabling a vertex attrib array failed"),
		sge::renderer::exception
	)
}
