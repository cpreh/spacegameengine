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


#ifndef SGE_D3D_CONSTANTS_HPP_INCLUDED
#define SGE_D3D_CONSTANTS_HPP_INCLUDED

#include "d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class constants {
public:
	static const unsigned back_buffer_count = 1;
	static const bool enable_auto_depth_stencil = true;
	static D3DSWAPEFFECT swap_effect() { return D3DSWAPEFFECT_DISCARD; }
	static const DWORD flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
};

}
}

#endif
