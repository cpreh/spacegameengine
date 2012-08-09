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
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/devicefuncs/create_texture.hpp>
#include <sge/d3d9/surfacefuncs/lock_rect.hpp>
#include <sge/d3d9/surfacefuncs/unlock_rect.hpp>
#include <sge/d3d9/texture/planar_types.hpp>


sge::d3d9::texture::planar_types::unique_ptr
sge::d3d9::texture::planar_types::create(
	IDirect3DDevice9 &_device,
	parameters const &_parameters,
	D3DFORMAT const _format,
	D3DPOOL const _pool,
	sge::d3d9::usage const _usage
)
{
	return
		sge::d3d9::devicefuncs::create_texture(
			_device,
			_parameters,
			_format,
			_pool,
			_usage
		);
}

D3DLOCKED_RECT const
sge::d3d9::texture::planar_types::lock(
	d3d_buffer &_buffer,
	lock_dest const &_lock_dest,
	sge::d3d9::lock_flags const _flags
)
{
	return
		sge::d3d9::surfacefuncs::lock_rect(
			_buffer,
			_lock_dest,
			_flags
		);
}

void
sge::d3d9::texture::planar_types::unlock(
	d3d_buffer &_buffer
)
{
	sge::d3d9::surfacefuncs::unlock_rect(
		_buffer
	);
}
