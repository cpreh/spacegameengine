//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_VOLUMEFUNCS_LOCK_BOX_HPP_INCLUDED
#define SGE_D3D9_VOLUMEFUNCS_LOCK_BOX_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/optional_lock_box_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace volumefuncs
{

D3DLOCKED_BOX const
lock_box(
	IDirect3DVolume9 &,
	sge::d3d9::optional_lock_box const &,
	sge::d3d9::lock_flags
);

}
}
}

#endif
