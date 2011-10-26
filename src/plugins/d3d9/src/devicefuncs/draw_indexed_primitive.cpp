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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/indexed_primitive.hpp>
#include <sge/d3d9/devicefuncs/draw_indexed_primitive.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


void
sge::d3d9::devicefuncs::draw_indexed_primitive(
	IDirect3DDevice9 *const _device,
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::indexed_primitive_type::type const _primitive_type,
	renderer::primitive_count const _primitive_count,
	renderer::first_index const _first_index
)
{
	if(
		_device->DrawIndexedPrimitive(
			convert::indexed_primitive(
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
				_primitive_count.get()
			)
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("DrawIndexedPrimitive() failed!")
		);
}
