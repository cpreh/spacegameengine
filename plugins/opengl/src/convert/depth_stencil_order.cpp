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


#include <sge/image/ds/format.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/depth_stencil_order.hpp>
#include <sge/opengl/convert/make_color_order.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::opengl::color_order
sge::opengl::convert::depth_stencil_order(
	sge::image::ds::format const _format
)
{
	switch(
		_format
	)
	{
	case sge::image::ds::format::d16:
	case sge::image::ds::format::d32:
		return
			sge::opengl::convert::make_color_order<
				GL_DEPTH_COMPONENT
			>();
	case sge::image::ds::format::d24s8:
		return
			sge::opengl::convert::make_color_order<
				GL_DEPTH_STENCIL
			>();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
