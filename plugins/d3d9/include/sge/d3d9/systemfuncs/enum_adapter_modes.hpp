//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_SYSTEMFUNCS_ENUM_ADAPTER_MODES_HPP_INCLUDED
#define SGE_D3D9_SYSTEMFUNCS_ENUM_ADAPTER_MODES_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device_index.hpp>
#include <sge/d3d9/optional_display_mode.hpp>


namespace sge
{
namespace d3d9
{
namespace systemfuncs
{

sge::d3d9::optional_display_mode
enum_adapter_modes(
	IDirect3D9 &,
	sge::d3d9::device_index,
	D3DFORMAT,
	UINT
);

}
}
}

#endif
