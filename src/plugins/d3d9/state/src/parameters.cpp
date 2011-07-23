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


#include "../parameters.hpp"

sge::d3d9::state::parameters::parameters(
	IDirect3DDevice9 *const _device,
	state::deferred::object &_deferred,
	state::clear &_clear
)
:
	device_(_device),
	deferred_(_deferred),
	clear_(_clear)
{
}

IDirect3DDevice9 *
sge::d3d9::state::parameters::device() const
{
	return device_;
}

sge::d3d9::state::deferred::object &
sge::d3d9::state::parameters::deferred() const
{
	return deferred_;
}

sge::d3d9::state::clear &
sge::d3d9::state::parameters::clear() const
{
	return clear_;
}
