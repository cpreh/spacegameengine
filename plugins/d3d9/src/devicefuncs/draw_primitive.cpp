//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/primitive_type.hpp>
#include <sge/d3d9/devicefuncs/draw_primitive.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/to_primitive_count.hpp>
#include <fcppt/text.hpp>


void
sge::d3d9::devicefuncs::draw_primitive(
	IDirect3DDevice9 &_device,
	sge::renderer::vertex::first const _first_vertex,
	sge::renderer::vertex::count const _num_vertices,
	sge::renderer::primitive_type const _primitive_type
)
{
	if(
		_device.DrawPrimitive(
			sge::d3d9::convert::primitive_type(
				_primitive_type
			),
			static_cast<
				UINT
			>(
				_first_vertex.get()
			),
			static_cast<
				UINT
			>(
				sge::renderer::vertex::to_primitive_count(
					_num_vertices,
					_primitive_type
				).get()
			)
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("DrawPrimitive() failed!")
		);
}
