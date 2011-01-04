/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../convert_vertex_colors.hpp"
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/image2d/algorithm/convert_conditional.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

void
sge::opengl::convert_vertex_colors(
	renderer::vf::dynamic::color const &_dcolor,
	renderer::size_type const _vertex_stride,
	renderer::size_type const _num_vertices,
	renderer::raw_pointer const _data,
	renderer::size_type const _offset
)
{
	sge::image2d::algorithm::convert_conditional(
		_data + _offset,
		sge::image2d::dim(
			1,
			_num_vertices
		),
		_dcolor.color_format(),
		sge::image2d::pitch(
			static_cast<
				sge::image2d::pitch::value_type
			>(
				_vertex_stride
			)
		),
		fcppt::assign::make_container<
			sge::image::algorithm::accepted_format_array
		>(
			sge::image::color::format::rgba8
		)(
			sge::image::color::format::rgba32f
		)
	);
}
