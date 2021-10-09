//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_DEVICEFUNCS_SET_TRANSFORM_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_SET_TRANSFORM_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>

namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

void set_transform(IDirect3DDevice9 &, D3DTRANSFORMSTATETYPE, D3DMATRIX const &);

}
}
}

#endif
