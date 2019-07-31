//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_DEVICEFUNCS_CREATE_DEPTH_STENCIL_SURFACE_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_CREATE_DEPTH_STENCIL_SURFACE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/multi_sample_quality.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

sge::d3d9::surface::d3d_unique_ptr
create_depth_stencil_surface(
	IDirect3DDevice9 &,
	sge::renderer::depth_stencil_buffer::surface_parameters const &,
	D3DMULTISAMPLE_TYPE,
	sge::d3d9::multi_sample_quality
);

}
}
}

#endif
