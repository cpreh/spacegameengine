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


#include <sge/renderer/device.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode3.hpp>
#include <sge/renderer/texture/set_address_mode2.hpp>
#include <sge/renderer/texture/set_address_mode3.hpp>
#include <sge/renderer/texture/stage.hpp>


void
sge::renderer::texture::set_address_mode3(
	sge::renderer::device &_device,
	sge::renderer::texture::stage const _stage,
	sge::renderer::texture::address_mode3 const &_mode
)
{
	sge::renderer::texture::set_address_mode2(
		_device,
		_stage,
		sge::renderer::texture::address_mode2(
			_mode.address_mode_s(),
			_mode.address_mode_t()
		)
	);

	_device.texture_address_mode_u(
		_mode.address_mode_u(),
		_stage
	);
}
