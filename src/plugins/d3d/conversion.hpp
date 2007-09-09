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


#ifndef SGE_D3D_CONVERSION_HPP_INCLUDED
#define SGE_D3D_CONVERSION_HPP_INCLUDED

#include "../../renderer/types.hpp"
#include "../../renderer/renderer_system.hpp"
#include "d3dinclude.hpp"

namespace sge
{
namespace d3d
{

template<typename L, typename R> L convert_cast (const R&);
template<> DWORD convert_cast (const resource_flag_t& r);
template<> D3DPOOL convert_cast (const resource_flag_t& r);
template<> D3DPRIMITIVETYPE convert_cast (const indexed_primitive_type& r);
template<> D3DPRIMITIVETYPE convert_cast (const nonindexed_primitive_type& r);
template<> D3DMULTISAMPLE_TYPE convert_cast (const multi_sample_type& r);
template<> D3DDECLUSAGE convert_cast (const vertex_usage& r);
template<> D3DTEXTURESTAGESTATETYPE convert_cast (const stage_op& r);
template<> D3DTEXTURESTAGESTATETYPE convert_cast (const stage_arg& r);
template<> DWORD convert_cast (const stage_op_value& r);
template<> DWORD convert_cast (const stage_arg_value& r);
//template<> D3DSAMPLERSTATETYPE convert_cast (const filter_arg& r);
template<> D3DTEXTUREFILTERTYPE convert_cast (const filter_value& r);
DWORD convert_lock_flags(lock_flag_t LF, resource_flag_t RF);

}
}
#endif
