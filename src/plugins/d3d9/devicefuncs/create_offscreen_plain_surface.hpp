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


#ifndef SGE_D3D9_DEVICEFUNCS_CREATE_OFFSCREEN_PLAIN_SURFACE_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_CREATE_OFFSCREEN_PLAIN_SURFACE_HPP_INCLUDED

#include "../d3dinclude.hpp"
#include "../d3d_surface_unique_ptr.hpp"
#include <sge/image/color/format.hpp>
#include <sge/renderer/dim2.hpp>

namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

d3d9::d3d_surface_unique_ptr
create_offscreen_plain_surface(
	IDirect3DDevice9 *,
	sge::renderer::dim2 const &,
	sge::image::color::format::type,
	D3DPOOL
);

}
}
}

#endif
