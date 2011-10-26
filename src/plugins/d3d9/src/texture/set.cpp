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


#include <sge/d3d9/devicefuncs/set_texture.hpp>
#include <sge/d3d9/texture/base.hpp>
#include <sge/d3d9/texture/set.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/const_optional_base.hpp>


void
sge::d3d9::texture::set(
	IDirect3DDevice9 *const _device,
	state::address_mode &_address_mode,
	renderer::stage const _stage,
	renderer::texture::const_optional_base const &_base
)
{
	devicefuncs::set_texture(
		_device,
		_stage,
		_base
	);

	if(
		_base
	)
		dynamic_cast<
			d3d9::texture::base const &
		>(
			*_base
		).address_mode(
			_device,
			_address_mode,
			_stage
		);
}
