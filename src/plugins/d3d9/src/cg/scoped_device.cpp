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
#include <sge/d3d9/cg/get_device.hpp>
#include <sge/d3d9/cg/scoped_device.hpp>
#include <sge/d3d9/cg/set_device.hpp>


sge::d3d9::cg::scoped_device::scoped_device(
	IDirect3DDevice9 *const _device
)
:
	old_(
		sge::d3d9::cg::get_device()
	),
	needs_reset_(
		old_
		!=
		_device
	)
{
	if(
		needs_reset_
	)
		sge::d3d9::cg::set_device(
			_device
		);
}

sge::d3d9::cg::scoped_device::~scoped_device()
{
	if(
		needs_reset_
	)
		sge::d3d9::cg::set_device(
			old_
		);
}
