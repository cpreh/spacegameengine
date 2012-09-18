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


#include <sge/image/color/object.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/bind_data_getter.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/lighting/material/color.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/phoenix/bind/bind_function_object.hpp>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor const
sge::opengl::state::ffp::lighting::material::color(
	GLenum const _face,
	GLenum const _what,
	sge::image::color::any::object const &_color
)
{
	return
		sge::opengl::state::wrap_error_handler<
			sge::opengl::state::actor
		>(
			boost::phoenix::bind(
				::glMaterialfv,
				_face,
				_what,
				boost::phoenix::bind(
					sge::opengl::state::bind_data_getter(
						sge::image::color::any::convert<
							sge::image::color::rgba32f_format
						>(
							_color
						)
					)
				)
			),
			FCPPT_TEXT("glMaterialfv")
		);
}
