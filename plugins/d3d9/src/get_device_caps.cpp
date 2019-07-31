//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device_index.hpp>
#include <sge/d3d9/get_device_caps.hpp>
#include <sge/d3d9/systemfuncs/get_caps.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/caps/clip_plane_indices.hpp>
#include <sge/renderer/caps/description.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/driver_name.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/max_anisotropy.hpp>
#include <sge/renderer/caps/max_texture_size.hpp>
#include <sge/renderer/caps/max_volume_texture_extent.hpp>
#include <sge/renderer/caps/non_power_of_2_textures.hpp>
#include <sge/renderer/caps/normalized_cvv.hpp>
#include <sge/renderer/caps/render_target_inverted.hpp>
#include <sge/renderer/caps/render_target_supported.hpp>
#include <sge/renderer/caps/srgb_framebuffer.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>


sge::renderer::caps::device
sge::d3d9::get_device_caps(
	IDirect3D9 &_system,
	sge::d3d9::device_index const _index
)
{
	D3DCAPS9 const caps(
		sge::d3d9::systemfuncs::get_caps(
			_system,
			_index
		)
	);

	D3DADAPTER_IDENTIFIER9 identifier;

	if(
		_system.GetAdapterIdentifier(
			_index.get(),
			0,
			&identifier
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("GetAdapterIdentifier failed")
		);

	return
		sge::renderer::caps::device(
			sge::renderer::caps::driver_name(
				fcppt::from_std_string(
					identifier.Driver
				)
			),
			sge::renderer::caps::description(
				fcppt::from_std_string(
					identifier.Description
				)
			),
			sge::renderer::caps::normalized_cvv(
				false
			),
			sge::renderer::caps::max_texture_size(
				sge::renderer::dim2(
					caps.MaxTextureWidth,
					caps.MaxTextureHeight
				)
			),
			sge::renderer::caps::max_volume_texture_extent(
				caps.MaxVolumeExtent
			),
			sge::renderer::caps::non_power_of_2_textures(
				!(
					caps.TextureCaps
					&
					(
						D3DPTEXTURECAPS_NONPOW2CONDITIONAL
						|
						D3DPTEXTURECAPS_POW2
					)
				)
			),
			sge::renderer::caps::max_anisotropy(
				caps.MaxAnisotropy
			),
			sge::renderer::caps::render_target_supported(
				true
			),
			sge::renderer::caps::render_target_inverted(
				false
			),
			sge::renderer::caps::clip_plane_indices(
				caps.MaxUserClipPlanes
			),
			sge::renderer::caps::light_indices(
				caps.MaxActiveLights
			),
			sge::renderer::caps::texture_stages(
				caps.MaxTextureBlendStages
			),
			sge::renderer::caps::target_surface_indices(
				caps.NumSimultaneousRTs
			),
			sge::renderer::caps::srgb_framebuffer(
				(
					caps.Caps3
					&
					D3DCAPS3_LINEAR_TO_SRGB_PRESENTATION
				)
				!=
				0u
			)
		);
}
