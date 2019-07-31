//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/viewport.hpp>
#include <sge/d3d9/devicefuncs/set_viewport.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <fcppt/text.hpp>


void
sge::d3d9::devicefuncs::set_viewport(
	IDirect3DDevice9 &_device,
	sge::renderer::target::viewport const &_viewport
)
{
	D3DVIEWPORT9 const d3d_viewport(
		sge::d3d9::convert::viewport(
			_viewport
		)
	);

	if(
		_device.SetViewport(
			&d3d_viewport
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetViewport() failed!")
		);
}
