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
#include <sge/opengl/light/color.hpp>
#include <sge/opengl/light/float_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/phoenix/core/value.hpp>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::index_actor const
sge::opengl::state::ffp::lighting::light::color(
	GLenum const _name,
	sge::image::color::any::object const &_object
)
{
	sge::image::color::rgba32f const color(
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_color
		)
	);

	return
		std::tr1::bind(
			::glLightfv,
			std::tr1::placeholders::_1,
			_name,
			boost::phoenix::bind(
				&sge::opengl::vector4::data,
				boost::phoenix::val(
					sge::opengl::vector4(
						color.data(),
						color.data_end()
					)
				)
			)
		);
}
