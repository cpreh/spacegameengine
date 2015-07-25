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


#include <sge/image/color/element_count.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/extra_elements.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/extra_any.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/variant/match.hpp>


GLint
sge::opengl::vf::extra_elements(
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
					fcppt::cast::size<
						GLint
					>(
						fcppt::cast::to_signed(
							_vector.element_count().get()
						)
					);
			},
			[](
				sge::renderer::vf::dynamic::color const &_color
			)
			{
				return
					fcppt::cast::size<
						GLint
					>(
						fcppt::cast::to_signed(
							sge::image::color::element_count(
								_color.color_format()
							)
						)
					);
			}
		);
}
