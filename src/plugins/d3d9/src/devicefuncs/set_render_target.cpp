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
#include <sge/d3d9/devicefuncs/set_render_target.hpp>
#include <sge/d3d9/surface/optional_d3d_ref.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
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
					fcppt::reference_wrapper<
						IDirect3DSurface9
					> const _surface_ref
				)
				{
					return
						_surface_ref.get_pointer();
				}
			)
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetRenderTarget() failed!")
		);
}
