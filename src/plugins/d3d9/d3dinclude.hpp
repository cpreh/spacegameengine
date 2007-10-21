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


#ifndef SGE_D3D9_D3DINCLUDE_HPP_INCLUDED
#define SGE_D3D9_D3DINCLUDE_HPP_INCLUDED

#include "../../shared_ptr.hpp"
#include "../../com_deleter.hpp"

#include "../../windows.hpp"
#include <d3d9.h>

namespace sge
{
namespace d3d9
{

typedef shared_ptr<IDirect3D9,com_deleter>                  d3d_ptr;
typedef shared_ptr<IDirect3DDevice9,com_deleter>            d3d_device_ptr;
typedef shared_ptr<IDirect3DCubeTexture9,com_deleter>       d3d_cube_texture_ptr;
typedef shared_ptr<IDirect3DTexture9,com_deleter>           d3d_texture_ptr;
typedef shared_ptr<IDirect3DVolumeTexture9,com_deleter>     d3d_volume_texture_ptr;
typedef shared_ptr<IDirect3DIndexBuffer9,com_deleter>       d3d_index_buffer_ptr;
typedef shared_ptr<IDirect3DVertexBuffer9,com_deleter>      d3d_vertex_buffer_ptr;
typedef shared_ptr<IDirect3DSurface9,com_deleter>           d3d_surface_ptr;
typedef shared_ptr<IDirect3DVertexDeclaration9,com_deleter> d3d_vertex_declaration_ptr;

}
}

#endif
