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


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/clear/back_buffer.hpp>
#include <sge/opengl/clear/depth_buffer.hpp>
#include <sge/opengl/clear/set.hpp>
#include <sge/opengl/clear/stencil_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/clear/back_buffer_value.hpp>
#include <sge/renderer/clear/depth_buffer_value.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/clear/stencil_buffer_value.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::clear::set(
	sge::renderer::clear::parameters const &_parameters
)
{
	GLenum flags(
		0
	);

	fcppt::optional::maybe_void(
		_parameters.back_buffer(),
		[
			&flags
		](
			sge::renderer::clear::back_buffer_value const &_back_buffer
		)
		{
			flags |= GL_COLOR_BUFFER_BIT;

			sge::opengl::clear::back_buffer(
				_back_buffer
			);
		}
	);

	fcppt::optional::maybe_void(
		_parameters.depth_buffer(),
		[
			&flags
		](
			sge::renderer::clear::depth_buffer_value const _depth_buffer
		)
		{
			flags |= GL_DEPTH_BUFFER_BIT;

			sge::opengl::clear::depth_buffer(
				_depth_buffer
			);
		}
	);

	fcppt::optional::maybe_void(
		_parameters.stencil_buffer(),
		[
			&flags
		](
			sge::renderer::clear::stencil_buffer_value const _stencil_buffer
		)
		{
			flags |= GL_STENCIL_BUFFER_BIT;

			sge::opengl::clear::stencil_buffer(
				_stencil_buffer
			);
		}
	);

	sge::opengl::call(
		::glClear,
		flags
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glClear failed"),
		sge::renderer::exception
	)
}
