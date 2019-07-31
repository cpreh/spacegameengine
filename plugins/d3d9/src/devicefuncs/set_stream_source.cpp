//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_stream_source.hpp>
#include <sge/d3d9/vertex/buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/static_downcast.hpp>


void
sge::d3d9::devicefuncs::set_stream_source(
	IDirect3DDevice9 &_device,
	sge::renderer::vertex::buffer const &_vertex_buffer,
	bool const _set
)
{
	sge::d3d9::vertex::buffer const &d3d_buffer(
		fcppt::cast::static_downcast<
			sge::d3d9::vertex::buffer const &
		>(
			_vertex_buffer
		)
	);

	if(
		_device.SetStreamSource(
			_vertex_buffer.format_part_index().get(),
			_set
			?
				&d3d_buffer.get()
			:
				nullptr
			,
			0u, // offset
			static_cast<
				UINT
			>(
				d3d_buffer.stride().get()
			)
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetStreamSource() failed!")
		);
}
