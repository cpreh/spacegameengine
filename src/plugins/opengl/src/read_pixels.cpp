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
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/read_pixels.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_void_ptr.hpp>


void
sge::opengl::read_pixels(
	sge::renderer::pixel_unit const _pos_x,
	sge::renderer::pixel_unit const _pos_y,
	sge::renderer::screen_unit const _width,
	sge::renderer::screen_unit const _height,
	sge::opengl::color_format const _format,
	sge::opengl::color_format_type const _format_type,
	sge::renderer::raw_pointer const _dest
)
{
	sge::opengl::call(
		::glReadPixels,
		fcppt::cast::size<
			GLint
		>(
			_pos_x
		),
		fcppt::cast::size<
			GLint
		>(
			_pos_y
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_width
			)
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_height
			)
		),
		_format.get(),
		_format_type.get(),
		fcppt::cast::to_void_ptr(
			_dest
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glReadPixels failed"),
		sge::renderer::exception
	)
}
