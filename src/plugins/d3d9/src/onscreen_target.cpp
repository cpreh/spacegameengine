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


#include "../onscreen_target.hpp"
#include "../basic_target_impl.hpp"

sge::d3d9::onscreen_target::onscreen_target(
	IDirect3DDevice9 *const _device,
	sge::renderer::viewport const &_viewport
)
:
	base(
		_device,
		_viewport
	)
{
	base::active(
		true
	);
}

sge::d3d9::onscreen_target::~onscreen_target()
{
}

sge::renderer::color_surface_ptr const
sge::d3d9::onscreen_target::surface() const
{
	return renderer::color_surface_ptr();
}

template class
sge::d3d9::basic_target<
	sge::renderer::onscreen_target
>;
