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
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/devicefuncs/create_vertex_buffer.hpp>
#include <sge/d3d9/vertex/d3d_buffer_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>


sge::d3d9::vertex::d3d_buffer_unique_ptr
sge::d3d9::devicefuncs::create_vertex_buffer(
	IDirect3DDevice9 &_device,
	sge::renderer::size_type const _size,
	D3DPOOL const _pool,
	sge::d3d9::usage const _usage
)
{
	IDirect3DVertexBuffer9 *ret;

	if(
		_device.CreateVertexBuffer(
			fcppt::cast::size<
				UINT
			>(
				_size
				
			),
			_usage.get(),
			0, // no FVF
			_pool,
			&ret,
			nullptr
		)
		!= D3D_OK
	)
		throw 
			sge::renderer::exception{
				FCPPT_TEXT("Cannot create vertex buffer!")
			};

	return
		sge::d3d9::vertex::d3d_buffer_unique_ptr(
			ret
		);
}
