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
#include <sge/d3d9/devicefuncs/set_sampler_state.hpp>
#include <sge/d3d9/texture/filter/anisotropic.hpp>
#include <sge/d3d9/texture/filter/anisotropic_level.hpp>
#include <sge/d3d9/texture/filter/convert/anisotropic_mip.hpp>
#include <sge/renderer/texture/filter/anisotropic/object.hpp>


void
sge::d3d9::texture::filter::anisotropic(
	IDirect3DDevice9 *const _device,
	renderer::texture::stage const _stage,
	renderer::texture::filter::anisotropic::object const &_object
)
{
	filter::anisotropic_level(
		_device,
		_stage,
		_object.level()
	);

	devicefuncs::set_sampler_state(
		_device,
		_stage,
		D3DSAMP_MAGFILTER,
		D3DTEXF_ANISOTROPIC
	);

	devicefuncs::set_sampler_state(
		_device,
		_stage,
		D3DSAMP_MINFILTER,
		D3DTEXF_ANISOTROPIC
	);

	devicefuncs::set_sampler_state(
		_device,
		_stage,
		D3DSAMP_MIPFILTER,
		filter::convert::anisotropic_mip(
			_object.mip()
		)
	);
}
