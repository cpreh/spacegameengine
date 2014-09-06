/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/lighting/material/color.hpp>
#include <fcppt/text.hpp>


sge::opengl::state::actor
sge::opengl::state::ffp::lighting::material::color(
	GLenum const _face,
	GLenum const _what,
	sge::image::color::any::object const &_color
)
{
	sge::image::color::rgba32f const converted{
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_color
		)
	};

	return
		sge::opengl::state::wrap_error_handler<
			sge::opengl::state::actor
		>(
			[
				_face,
				_what,
				converted
			]
			{
				::glMaterialfv(
					_face,
					_what,
					converted.data()
				);
			},
			FCPPT_TEXT("glMaterialfv")
		);
}
