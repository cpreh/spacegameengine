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


#include "../convert_vertices.hpp"
#include "../convert_vertex_colors.hpp"
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <sge/renderer/vf/dynamic/unspecified.hpp>
#include <fcppt/variant/holds_type.hpp>

namespace
{

template<
	typename Type
>
void
convert_if_color(
	Type const &_type,
	sge::renderer::size_type const _vertex_stride,
	sge::renderer::size_type const _num_vertices,
	sge::renderer::raw_pointer const _data,
	sge::renderer::size_type const _offset
)
{
	if(
		fcppt::variant::holds_type<
			sge::renderer::vf::dynamic::color
		>(
			_type
		)
	)
		sge::opengl::convert_vertex_colors(
			_type. template get<
				sge::renderer::vf::dynamic::color
			>(),
			_vertex_stride,
			_num_vertices,
			_data,
			_offset
		);
}

}

void
sge::opengl::convert_vertices(
	renderer::vf::dynamic::ordered_element const &_ordered_element,
	renderer::size_type const _vertex_stride,
	renderer::size_type const _num_vertices,
	renderer::raw_pointer const _data
)
{
	renderer::vf::dynamic::element const element(
		_ordered_element.element()
	);

	::convert_if_color(
		element.info(),
		_vertex_stride,
		_num_vertices,
		_data,
		_ordered_element.offset()
	);
	
	if(
		fcppt::variant::holds_type<
			sge::renderer::vf::dynamic::unspecified
		>(
			element.info()
		)
	)
		::convert_if_color(
			element.info().get<
				renderer::vf::dynamic::unspecified
			>().type(),
			_vertex_stride,
			_num_vertices,
			_data,
			_ordered_element.offset()
		);
}
