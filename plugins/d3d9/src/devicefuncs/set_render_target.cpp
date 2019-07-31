//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_render_target.hpp>
#include <sge/d3d9/surface/optional_d3d_ref.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::d3d9::devicefuncs::set_render_target(
	IDirect3DDevice9 &_device,
	sge::renderer::target::surface_index const _index,
	sge::d3d9::surface::optional_d3d_ref const &_surface
)
{
	if(
		_device.SetRenderTarget(
			fcppt::cast::size<
				DWORD
			>(
				_index.get()
			),
			fcppt::optional::maybe(
				_surface,
				[]()
				-> IDirect3DSurface9 *
				{
					return
						nullptr;
				},
				[](
					fcppt::reference<
						IDirect3DSurface9
					> const _surface_ref
				)
				{
					return
						&_surface_ref.get();
				}
			)
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetRenderTarget() failed!")
		);
}
