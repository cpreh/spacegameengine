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


#include <sge/d3d9/create_caps.hpp>
#include <sge/d3d9/systemfuncs/get_caps.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/filter/anisotropic/level.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>


namespace
{

	/*
void
add_display_modes(
				  display_mode_array& v,
	sge::renderer::adapter_type const adapter,
	sge::renderer::bit_depth::type const depth,
	D3DFORMAT const format,
	sge::d3d9::d3d_ptr const sys)
{
	unsigned const modes = sys->GetAdapterModeCount(adapter,format);

	for(unsigned i = 0; i < modes; ++i)
	{
		D3DDISPLAYMODE mode;

		sys->EnumAdapterModes(
			adapter,
			format,
			i,
			&mode
		);

		if(mode.Width >= 640 && mode.Height >= 480)
			v.push_back(
				sge::renderer::display_mode(
					mode.Width,
					mode.Height,
					depth,
					mode.RefreshRate
				)
			);
	}
}
*/
}

sge::renderer::caps const
sge::d3d9::create_caps(
	IDirect3D9 *const _system,
	renderer::adapter const _adapter
)
{
	D3DCAPS9 const caps(
		d3d9::systemfuncs::get_caps(
			_system,
			_adapter
		)
	);

	D3DADAPTER_IDENTIFIER9 identifier;

	if(
		_system->GetAdapterIdentifier(
			_adapter.get(),
			0,
			&identifier
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("GetAdapterIdentifier failed")
		);

	/*display_mode_array display_modes;
	add_display_modes(display_modes, adapter, bit_depth::depth16, D3DFMT_A1R5G5B5, sys);
	add_display_modes(display_modes, adapter, bit_depth::depth16, D3DFMT_X1R5G5B5, sys);
	add_display_modes(display_modes, adapter, bit_depth::depth16, D3DFMT_R5G6B5,   sys);
	add_display_modes(display_modes, adapter, bit_depth::depth32, D3DFMT_A8R8G8B8, sys);
	add_display_modes(display_modes, adapter, bit_depth::depth32, D3DFMT_X8R8G8B8, sys);*/

	return
		renderer::caps(
			_adapter,
			fcppt::from_std_string(
				identifier.Driver
			),
			fcppt::from_std_string(
				identifier.Description
			),
			sge::renderer::dim2(
				caps.MaxTextureWidth,
				caps.MaxTextureHeight
			),
			static_cast<
				sge::renderer::size_type
			>(
				caps.MaxVolumeExtent
			),
			sge::renderer::texture::filter::anisotropic::level(
				caps.MaxAnisotropy
			),
			false, // FIXME: find out if render to texture is supported
			false, // no glsl
			sge::image::color::format::bgra8
		);
}
