#ifndef SGE_D3D_CONVERSION_HPP_INCLUDED
#define SGE_D3D_CONVERSION_HPP_INCLUDED

#include "../../renderer/renderer_types.hpp"
#include "../../renderer/renderer_system.hpp"

#include "./d3dinclude.hpp"

namespace sge
{

enum resource_flags;
enum primitive_type;
enum text_flags;

namespace d3d
{

template<typename L, typename R> L convert_cast (const R&);
template<> DWORD convert_cast (const lock_flag_t& r);
template<> D3DPOOL convert_cast (const resource_flag_t& r);
template<> D3DPRIMITIVETYPE convert_cast (const primitive_type& r);
template<> DWORD convert_cast (const text_flags& r);
template<> D3DMULTISAMPLE_TYPE convert_cast (const multi_sample_type& r);
template<> D3DDECLUSAGE convert_cast (const vertex_usage& r);
template<> D3DTRANSFORMSTATETYPE convert_cast (const matrix_usage& r);
template<> D3DTEXTURESTAGESTATETYPE convert_cast (const stage_op& r);
template<> D3DTEXTURESTAGESTATETYPE convert_cast (const stage_arg& r);
template<> DWORD convert_cast (const stage_op_value& r);
template<> DWORD convert_cast (const stage_arg_value& r);
template<> D3DSAMPLERSTATETYPE convert_cast (const filter_arg& r);
template<> D3DTEXTUREFILTERTYPE convert_cast (const filter_arg_value& r);
DWORD convert_lock_flags(lock_flag_t LF, resource_flag_t RF);

inline color rgba_to_argb(const color c)
{
	return (c >> 8) | ((c & 0xFF) << 24);
}

}
}
#endif
