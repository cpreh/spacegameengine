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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/primitive_type.hpp>
#include <sge/d3d9/devicefuncs/draw_indexed_primitive.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/to_primitive_count.hpp>
#include <fcppt/text.hpp>


void
sge::d3d9::devicefuncs::draw_indexed_primitive(
	IDirect3DDevice9 &_device,
	sge::renderer::vertex::first const _first_vertex,
	sge::renderer::vertex::count const _num_vertices,
	sge::renderer::primitive_type const _primitive_type,
	sge::renderer::index::first const _first_index,
	sge::renderer::index::count const _num_indices
)
{
	if(
		_primitive_type
		==
		sge::renderer::primitive_type::point_list
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Rendering indexed point lists is not supported in D3D9!")
		);

	if(
		_device.DrawIndexedPrimitive(
			sge::d3d9::convert::primitive_type(
				_primitive_type
			),
			0,
			static_cast<
				UINT
			>(
				_first_vertex.get()
			),
			static_cast<
				UINT
			>(
				_num_vertices.get()
			),
			static_cast<
				UINT
			>(
				_first_index.get()
			),
			static_cast<
				UINT
			>(
				sge::renderer::vertex::to_primitive_count(
					sge::renderer::vertex::count(
						_num_indices.get()
					),
					_primitive_type
				).get()
			)
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("DrawIndexedPrimitive() failed!")
		);
}
