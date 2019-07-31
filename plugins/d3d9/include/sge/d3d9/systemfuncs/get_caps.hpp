//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_SYSTEMFUNCS_GET_CAPS_HPP_INCLUDED
#define SGE_D3D9_SYSTEMFUNCS_GET_CAPS_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device_index.hpp>


namespace sge
{
namespace d3d9
{
namespace systemfuncs
{

D3DCAPS9
get_caps(
	IDirect3D9 &,
	sge::d3d9::device_index
);

}
}
}

#endif
