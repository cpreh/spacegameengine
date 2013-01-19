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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/clear/back_buffer.hpp>
#include <sge/opengl/clear/depth_buffer.hpp>
#include <sge/opengl/clear/set.hpp>
#include <sge/opengl/clear/stencil_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::clear::set(
	sge::renderer::clear::parameters const &_parameters
)
{
	GLenum flags(
		0
	);

	if(
		_parameters.back_buffer()
	)
	{
		flags |= GL_COLOR_BUFFER_BIT;

		sge::opengl::clear::back_buffer(
			*_parameters.back_buffer()
		);
	}

	if(
		_parameters.depth_buffer()
	)
	{
		flags |= GL_DEPTH_BUFFER_BIT;

		sge::opengl::clear::depth_buffer(
			*_parameters.depth_buffer()
		);
	}

	if(
		_parameters.stencil_buffer()
	)
	{
		flags |= GL_STENCIL_BUFFER_BIT;

		sge::opengl::clear::stencil_buffer(
			*_parameters.stencil_buffer()
		);
	}

	::glClear(
		flags
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glClear failed"),
		sge::renderer::exception
	)
}
