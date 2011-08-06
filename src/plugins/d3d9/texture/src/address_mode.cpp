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


#include "../address_mode.hpp"
#include "../../convert/address_mode.hpp"
#include "../../devicefuncs/set_sampler_state.hpp"
#include "../../state/address_mode.hpp"
#include "../../d3dinclude.hpp"
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode3.hpp>

namespace
{

void
update_level(
	IDirect3DDevice9 *,
	sge::d3d9::state::address_mode &,
	sge::renderer::stage,
	D3DSAMPLERSTATETYPE,
	D3DTEXTUREADDRESS
);

}

void
sge::d3d9::texture::address_mode(
	IDirect3DDevice9 *const _device,
	state::address_mode &_state,
	renderer::stage const _stage,
	renderer::texture::address_mode2 const &_mode
)
{
	::update_level(
		_device,
		_state,
		_stage,
		D3DSAMP_ADDRESSU,
		d3d9::convert::address_mode(
			_mode.address_mode_s().get()
		)
	);

	::update_level(
		_device,
		_state,
		_stage,
		D3DSAMP_ADDRESSV,
		d3d9::convert::address_mode(
			_mode.address_mode_t().get()
		)
	);
}

void
sge::d3d9::texture::address_mode(
	IDirect3DDevice9 *const _device,
	state::address_mode &_state,
	renderer::stage const _stage,
	renderer::texture::address_mode3 const &_mode
)
{
	texture::address_mode(
		_device,
		_state,
		_stage,
		renderer::texture::address_mode2(
			_mode.address_mode_s(),
			_mode.address_mode_t()
		)
	);

	::update_level(
		_device,
		_state,
		_stage,
		D3DSAMP_ADDRESSW,
		d3d9::convert::address_mode(
			_mode.address_mode_u().get()
		)
	);
}

namespace
{

void
update_level(
	IDirect3DDevice9 *const _device,
	sge::d3d9::state::address_mode &_state,
	sge::renderer::stage const _stage,
	D3DSAMPLERSTATETYPE const _level,
	D3DTEXTUREADDRESS const _value
)
{
	if(
		_state.update(
			_stage,
			_level,
			_value
		)
	)
		sge::d3d9::devicefuncs::set_sampler_state(
			_device,
			_stage,
			_level,
			_value
		);
}

}
