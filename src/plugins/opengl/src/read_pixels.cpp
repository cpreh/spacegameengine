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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/read_pixels.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::read_pixels(
	renderer::pixel_unit const _pos_x,
	renderer::pixel_unit const _pos_y,
	renderer::size_type const _width,
	renderer::size_type const _height,
	opengl::color_format const _format,
	opengl::color_format_type const _format_type,
	renderer::raw_pointer const _dest
)
{
	::glReadPixels(
		static_cast<
			GLint
		>(
			_pos_x
		),
		static_cast<
			GLint
		>(
			_pos_y
		),
		static_cast<
			GLsizei
		>(
			_width
		),
		static_cast<
			GLsizei
		>(
			_height
		),
		_format.get(),
		_format_type.get(),
		_dest
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glReadPixels failed"),
		sge::renderer::exception
	)
}
