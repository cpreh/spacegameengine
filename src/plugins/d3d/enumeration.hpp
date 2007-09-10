/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D_ENUMERATION_HPP_INCLUDED
#define SGE_D3D_ENUMERATION_HPP_INCLUDED

#include "renderer_system.hpp"
#include "../../win32_window.hpp"

#include "d3dinclude.hpp"

namespace sge
{
namespace d3d
{

void create_renderer_caps(unsigned adapter, d3d_ptr sys, renderer_caps& caps);

DWORD get_tnl_caps(unsigned adapter, d3d_ptr sys);

void add_display_modes(display_mode_array& v, unsigned adapter, bit_depth::type depth, D3DFORMAT format, d3d_ptr sys);

D3DFORMAT search_format(const display_mode& mode, d3d_ptr sys );

D3DFORMAT search_stencil_format(unsigned adapter, D3DFORMAT screen_format, d3d_ptr sys);

D3DPRESENT_PARAMETERS create_present_parameters(const renderer_parameters& param, int adapter, win32_window_ptr wnd, d3d_ptr sys);

}
}

#endif
