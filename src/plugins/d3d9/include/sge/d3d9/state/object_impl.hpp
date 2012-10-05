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


#ifndef SGE_D3D9_STATE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_D3D9_STATE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_render_state.hpp>
#include <sge/d3d9/state/object.hpp>
#include <sge/d3d9/state/render_vector.hpp>


template<
	typename State
>
sge::d3d9::state::object<
	State
>::object(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::render_vector const &_states
)
:
	device_(
		_device
	),
	states_(
		_states
	)
{
}

template<
	typename State
>
sge::d3d9::state::object<
	State
>::~object()
{
}

template<
	typename State
>
void
sge::d3d9::state::object<
	State
>::set() const
{
	for(
		sge::d3d9::state::render_vector::const_iterator it(
			states_.begin()
		);
		it != states_.end();
		++it
	)
		sge::d3d9::devicefuncs::set_render_state(
			device_,
			it->state(),
			it->value()
		);
}

#endif
