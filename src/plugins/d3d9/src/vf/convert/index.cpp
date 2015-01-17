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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/d3d9/vf/convert/index.hpp>
#include <sge/d3d9/vf/convert/index_visitor.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


BYTE
sge::d3d9::vf::convert::index(
	sge::renderer::vf::dynamic::element const &_element,
	sge::d3d9::vf::texture_coordinate_count const _texture_coordinates
)
{
	return
		fcppt::variant::apply_unary(
			sge::d3d9::vf::convert::index_visitor(
				_texture_coordinates
			),
			_element.info()
		);
}
