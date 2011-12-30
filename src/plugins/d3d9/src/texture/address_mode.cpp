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
#include <sge/d3d9/convert/address_mode.hpp>
#include <sge/d3d9/convert/address_mode_type.hpp>
#include <sge/d3d9/devicefuncs/set_sampler_state.hpp>
#include <sge/d3d9/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>
#include <sge/renderer/texture/stage.hpp>


template<
	typename Mode
>
void
sge::d3d9::texture::address_mode(
	IDirect3DDevice9 *const _device,
	renderer::texture::stage const _stage,
	Mode const _mode
)
{
	sge::d3d9::devicefuncs::set_sampler_state(
		_device,
		_stage,
		d3d9::convert::address_mode_type<
			Mode
		>::get(),
		d3d9::convert::address_mode(
			_mode.get()
		)
	);
}

#define SGE_D3D9_TEXTURE_INSTANTIATE_ADDRESS_MODE( \
	mode_type \
) \
template \
void \
sge::d3d9::texture::address_mode<\
	mode_type \
>( \
	IDirect3DDevice9 *const, \
	sge::renderer::texture::stage const, \
	mode_type const \
)

SGE_D3D9_TEXTURE_INSTANTIATE_ADDRESS_MODE(
	sge::renderer::texture::address_mode_s
);

SGE_D3D9_TEXTURE_INSTANTIATE_ADDRESS_MODE(
	sge::renderer::texture::address_mode_t
);

SGE_D3D9_TEXTURE_INSTANTIATE_ADDRESS_MODE(
	sge::renderer::texture::address_mode_u
);
