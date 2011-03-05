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


#ifndef SGE_D3D9_BASIC_TARGET_HPP_INCLUDED
#define SGE_D3D9_BASIC_TARGET_HPP_INCLUDED

#include "basic_target.hpp"
#include <fcppt/math/box/basic_impl.hpp>

template<
	typename Base
>
sge::d3d9::basic_target<Base>::basic_target(
	IDirect3DDevice9 *const _device
)
:
	device_(_device),
	viewport_(
		sge::renderer::viewport::value_type::null()
	)
{
}

sge::d3d9::basic_target<Base>::~basic_target()
{
}

void
sge::d3d9::basic_target<Base>::viewport(
	renderer::viewport const &_viewport
)
{
	viewport_ = _viewport;
}

sge::renderer::viewport const
sge::d3d9::basic_target<Base>::viewport() const
{
	return viewport_;
}

#endif
