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


#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/clear/back_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/clear/back_buffer_value.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::clear::back_buffer(
	sge::renderer::clear::back_buffer_value const &_value
)
{
	sge::image::color::rgba32f const fcolor(
		image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_value
		)
	);

	::glClearColor(
		fcolor.get(
			mizuiro::color::channel::red()
		),
		fcolor.get(
			mizuiro::color::channel::green()
		),
		fcolor.get(
			mizuiro::color::channel::blue()
		),
		fcolor.get(
			mizuiro::color::channel::alpha()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glClearColor failed"),
		sge::renderer::exception
	)
}
