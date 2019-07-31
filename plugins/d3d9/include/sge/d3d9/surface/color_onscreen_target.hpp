//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_SURFACE_COLOR_ONSCREEN_TARGET_HPP_INCLUDED
#define SGE_D3D9_SURFACE_COLOR_ONSCREEN_TARGET_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/color_create_function.hpp>


namespace sge
{
namespace d3d9
{
namespace surface
{

sge::d3d9::surface::color_create_function
color_onscreen_target(
	IDirect3DDevice9 &
);

}
}
}

#endif
