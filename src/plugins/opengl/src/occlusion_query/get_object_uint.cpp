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
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/occlusion_query/context.hpp>
#include <sge/opengl/occlusion_query/get_object_uint.hpp>
#include <sge/opengl/occlusion_query/id.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


GLuint
sge::opengl::occlusion_query::get_object_uint(
	sge::opengl::occlusion_query::context const &_context,
	sge::opengl::occlusion_query::id const _id,
	GLenum const _what
)
{
	GLuint result;

	_context.get_query_object_uiv()(
		_id.get(),
		_what,
		&result
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Getting an unsigned int from an occlusion query failed"),
		sge::renderer::exception
	)

	return result;
}
