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


#include <sge/image/color/object_impl.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/opengl/light/color.hpp>
#include <sge/opengl/light/float_ptr.hpp>
#include <fcppt/variant/object.hpp>


void
sge::opengl::light::color(
	light::index const _index,
	GLenum const _name,
	sge::image::color::any::object const &_color
)
{
	light::float_ptr(
		_index,
		_name,
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_color
		).data()
	);
}
