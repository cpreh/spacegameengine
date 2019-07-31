//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_QUERYFUNCS_GET_DWORD_HPP_INCLUDED
#define SGE_D3D9_QUERYFUNCS_GET_DWORD_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/queryfuncs/optional_dword_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace queryfuncs
{

sge::d3d9::queryfuncs::optional_dword const
get_dword(
	IDirect3DQuery9 &,
	DWORD flags
);

}
}
}

#endif
