#ifndef SGE_D3D_D3DINCLUDE_HPP_INCLUDED
#define SGE_D3D_D3DINCLUDE_HPP_INCLUDED

#include "../../main/shared_ptr.hpp"

#ifdef SGE_WINDOWS_PLATFORM
#define WIN32_LEAN_AND_MEAN
#include <d3d9.h>
#else
#include <wine/windows/d3d9.h>
#endif

namespace sge
{
namespace d3d
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
