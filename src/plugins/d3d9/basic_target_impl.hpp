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


#ifndef SGE_D3D9_BASIC_TARGET_IMPL_HPP_INCLUDED
#define SGE_D3D9_BASIC_TARGET_IMPL_HPP_INCLUDED

#include "basic_target.hpp"
#include "devicefuncs/set_scissor_rect.hpp"
#include "devicefuncs/set_viewport.hpp"
#include <fcppt/math/box/basic_impl.hpp>

template<
	typename Base
>
sge::d3d9::basic_target<Base>::basic_target(
	IDirect3DDevice9 *const _device,
	sge::renderer::viewport const &_viewport
)
:
	device_(_device),
	active_(false),
	viewport_(_viewport),
	scissor_area_(
		renderer::scissor_area(
			_viewport.get()
		)
	)
{
}

template<
	typename Base
>
sge::d3d9::basic_target<Base>::~basic_target()
{
}

template<
	typename Base
>
void
sge::d3d9::basic_target<Base>::viewport(
	renderer::viewport const &_viewport
)
{
	viewport_ = _viewport;

	this->check_viewport();
}

template<
	typename Base
>
sge::renderer::viewport const
sge::d3d9::basic_target<Base>::viewport() const
{
	return viewport_;
}

template<
	typename Base
>
void
sge::d3d9::basic_target<Base>::scissor_area(
	renderer::scissor_area const &_scissor_area
)
{
	scissor_area_ = _scissor_area;

	this->check_scissor_area();
}

template<
	typename Base
>
sge::renderer::scissor_area const
sge::d3d9::basic_target<Base>::scissor_area() const
{
	return scissor_area_;
}

template<
	typename Base
>
void
sge::d3d9::basic_target<Base>::active(
	bool const _active
)
{
	active_ = _active;

	this->check_viewport();

	this->check_scissor_area();
}

template<
	typename Base
>
void
sge::d3d9::basic_target<Base>::check_viewport()
{
	if(
		active_
	)
		devicefuncs::set_viewport(
			device_,
			viewport_
		);
}

template<
	typename Base
>
void
sge::d3d9::basic_target<Base>::check_scissor_area()
{
	if(
		active_
	)
		devicefuncs::set_scissor_rect(
			device_,
			scissor_area_
		);
}

#endif
