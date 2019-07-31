//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/index_buffer.hpp>
#include <sge/d3d9/devicefuncs/set_index_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/static_downcast.hpp>


void
sge::d3d9::devicefuncs::set_index_buffer(
	IDirect3DDevice9 &_device,
	sge::renderer::index::buffer const &_index_buffer
)
{
	if(
		_device.SetIndices(
			&fcppt::cast::static_downcast<
				sge::d3d9::index_buffer const &
			>(
				_index_buffer
			).get()
		)
		!=
		D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("set_index_buffer() failed")
		);
}
