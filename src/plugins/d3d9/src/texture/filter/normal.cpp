/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/d3d9/texture/filter/anisotropic_level.hpp>
#include <sge/d3d9/texture/filter/normal.hpp>
#include <sge/d3d9/texture/filter/convert/mag.hpp>
#include <sge/d3d9/texture/filter/convert/min.hpp>
#include <sge/d3d9/texture/filter/convert/normal_mip.hpp>
#include <sge/renderer/texture/filter/anisotropic/level.hpp>
#include <sge/renderer/texture/filter/normal/object.hpp>


void
sge::d3d9::texture::filter::normal(
	IDirect3DDevice9 *const _device,
	renderer::texture::stage const _stage,
	renderer::texture::filter::normal::object const &_object
)
{
	filter::anisotropic_level(
		_device,
		_stage,
		renderer::texture::filter::anisotropic::level(
			1u
		)
	);

	devicefuncs::set_sampler_state(
		_device,
		_stage,
		D3DSAMP_MAGFILTER,
		filter::convert::mag(
			_object.mag()
		)
	);

	devicefuncs::set_sampler_state(
		_device,
		_stage,
		D3DSAMP_MINFILTER,
		filter::convert::min(
			_object.min()
		)
	);

	devicefuncs::set_sampler_state(
		_device,
		_stage,
		D3DSAMP_MIPFILTER,
		filter::convert::normal_mip(
			_object.mip()
		)
	);
}
