//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_DEVICEFUNCS_CREATE_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_CREATE_VERTEX_BUFFER_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/vertex/d3d_buffer_unique_ptr.hpp>
#include <sge/renderer/size_type.hpp>

namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

sge::d3d9::vertex::d3d_buffer_unique_ptr
create_vertex_buffer(IDirect3DDevice9 &, sge::renderer::size_type, D3DPOOL, sge::d3d9::usage);

}
}
}

#endif
