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


#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/color_to_format_type.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/opengl/vf/extra_format.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/extra_any.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/variant/match.hpp>


GLenum
sge::opengl::vf::extra_format(
	sge::renderer::vf::dynamic::extra_any const &_any
)
{
	return
		fcppt::variant::match(
			_any,
			[](
				sge::renderer::vf::dynamic::vector const &_vector
			)
			{
				return
					sge::opengl::vf::convert_element_type(
						_vector.element_type()
					);
			},
			[](
				sge::renderer::vf::dynamic::color const &_color
			)
			{
				return
					sge::opengl::convert::color_to_format_type(
						_color.color_format()
					).get();
			}
		);
}
