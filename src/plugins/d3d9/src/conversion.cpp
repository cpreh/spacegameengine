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


#include "../../../exception.hpp"
#include "../../../renderer/types.hpp"
#include "../conversion.hpp"

template<> DWORD sge::d3d9::convert_cast (const resource_flag_t& r)
{
	DWORD l = 0;
	if(r & resource_flags::dynamic)
		l |= D3DUSAGE_DYNAMIC;
	if(r & resource_flags::write_only)
		l |= D3DUSAGE_WRITEONLY;
    return l;
}

template<> D3DPOOL sge::d3d9::convert_cast (const resource_flag_t& r)
{
	return r & resource_flags::dynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
}

template<> D3DPRIMITIVETYPE sge::d3d9::convert_cast (const indexed_primitive_type::type& r)
{
	switch(r) {
	case indexed_primitive_type::line:
		return D3DPT_LINELIST;
	case indexed_primitive_type::triangle:
		return D3DPT_TRIANGLELIST;
	default:
		throw exception("Invalid indexed primitive type!");
	}
}

template<> D3DPRIMITIVETYPE sge::d3d9::convert_cast (const nonindexed_primitive_type::type& r)
{
	switch(r) {
	case nonindexed_primitive_type::point:
		return D3DPT_POINTLIST;
	case nonindexed_primitive_type::line_strip:
		return D3DPT_LINESTRIP;
	case nonindexed_primitive_type::triangle_strip:
		return D3DPT_TRIANGLESTRIP;
	case nonindexed_primitive_type::triangle_fan:
		return D3DPT_TRIANGLEFAN;
	default:
		throw exception("Invalid non indexed primitive type!");
	}

}

template<> D3DMULTISAMPLE_TYPE sge::d3d9::convert_cast (const multi_sample_type& r)
{
	switch(r) {
	case 0:
	case 1:
		return D3DMULTISAMPLE_NONE;
	case 2:
		return D3DMULTISAMPLE_2_SAMPLES;
	case 3:
		return D3DMULTISAMPLE_3_SAMPLES;
	case 4:
		return D3DMULTISAMPLE_4_SAMPLES;
	case 5:
		return D3DMULTISAMPLE_5_SAMPLES;
	case 6:
		return D3DMULTISAMPLE_6_SAMPLES;
	case 7:
		return D3DMULTISAMPLE_7_SAMPLES;
	case 8:
		return D3DMULTISAMPLE_8_SAMPLES;
	case 9:
		return D3DMULTISAMPLE_9_SAMPLES;
	case 10:
		return D3DMULTISAMPLE_10_SAMPLES;
	case 11:
		return D3DMULTISAMPLE_11_SAMPLES;
	case 12:
		return D3DMULTISAMPLE_12_SAMPLES;
	case 13:
		return D3DMULTISAMPLE_13_SAMPLES;
	case 14:
		return D3DMULTISAMPLE_14_SAMPLES;
	case 15:
		return D3DMULTISAMPLE_15_SAMPLES;
	case 16:
		return D3DMULTISAMPLE_16_SAMPLES;
	default:
		throw exception("Invalid multi_sample_type value (must be <= 16)!");
	}
}

template<> D3DDECLUSAGE sge::d3d9::convert_cast (const vertex_usage::type& r)
{
	switch(r) {
	case vertex_usage::pos:
		return D3DDECLUSAGE_POSITION;
	case vertex_usage::normal:
		return D3DDECLUSAGE_NORMAL;
	case vertex_usage::tex:
		return D3DDECLUSAGE_TEXCOORD;
	case vertex_usage::diffuse:
		return D3DDECLUSAGE_COLOR;
	default:
		throw exception("Invalid vertex_usage!");
	}
}

template<> D3DTEXTURESTAGESTATETYPE sge::d3d9::convert_cast (const texture_stage_op::type& r)
{
	switch(r) {
	case texture_stage_op::color:
		return D3DTSS_COLOROP;
	case texture_stage_op::alpha:
		return D3DTSS_ALPHAOP;
	default:
		throw exception("Invalid texture_stage_op!");
	}
}

template<> D3DTEXTURESTAGESTATETYPE sge::d3d9::convert_cast (const texture_stage_arg::type& r)
{
	// TODO: maybe we have to swap numbers here
	switch(r) {
	case texture_stage_arg::rgb0:
		return D3DTSS_COLORARG0;
	case texture_stage_arg::rgb1:
		return D3DTSS_COLORARG1;
	case texture_stage_arg::rgb2:
		return D3DTSS_COLORARG2;
	case texture_stage_arg::alpha0:
		return D3DTSS_ALPHAARG0;
	case texture_stage_arg::alpha1:
		return D3DTSS_ALPHAARG1;
	case texture_stage_arg::alpha2:
		return D3DTSS_ALPHAARG2;
	default:
		throw exception("Invalid texture_stage_arg!");
	}
}

template<> DWORD sge::d3d9::convert_cast (const texture_stage_op_value::type& r)
{
	switch(r) {
	//	return D3DTOP_DISABLE;
	//	return D3DTOP_SELECTARG1;
	//	return D3DTOP_SELECTARG2;
	//case texture_stage_op_value::arg0:
	//	return D3DTOP_SELECTARG0; // TODO: maybe we have to use a different arg number here
	case texture_stage_op_value::modulate:
		return D3DTOP_MODULATE;
	case texture_stage_op_value::modulate2x:
		return D3DTOP_MODULATE2X;
	case texture_stage_op_value::modulate4x:
		return D3DTOP_MODULATE4X;
	case texture_stage_op_value::add:
		return D3DTOP_ADD;
	case texture_stage_op_value::add_signed:
		return D3DTOP_ADDSIGNED;
	case texture_stage_op_value::add_signed2x:
		return D3DTOP_ADDSIGNED2X;
	case texture_stage_op_value::substract:
		return D3DTOP_SUBTRACT;
	//	return D3DTOP_ADDSMOOTH;
	//	return D3DTOP_BLENDDIFFUSEALPHA;
//		return D3DTOP_BLENDTEXTUREALPHA;
//		return D3DTOP_BLENDFACTORALPHA;
//		return D3DTOP_BLENDTEXTUREALPHAPM;
//		return D3DTOP_BLENDCURRENTALPHA;
//		return D3DTOP_PREMODULATE;
//		return D3DTOP_MODULATEALPHA_ADDCOLOR;
//		return D3DTOP_MODULATECOLOR_ADDALPHA;
//		return D3DTOP_MODULATEINVALPHA_ADDCOLOR;
//		return D3DTOP_MODULATEINVCOLOR_ADDALPHA;
//		return D3DTOP_BUMPENVMAP;
//		return D3DTOP_BUMPENVMAPLUMINANCE;
//		return D3DTOP_DOTPRODUCT3;
//		return D3DTOP_MULTIPLYADD;
//		return D3DTOP_LERP;
	default:
		throw exception("Invalid texture_stage_op_value!");
	}
}

template<> DWORD sge::d3d9::convert_cast (const texture_stage_arg_value::type& r)
{
	switch(r) {
	case texture_stage_arg_value::constant:
		return D3DTA_CONSTANT;
	case texture_stage_arg_value::current:
		return D3DTA_CURRENT;
//		return D3DTA_DIFFUSE;
//		return D3DTA_SPECULAR;
//		return D3DTA_TEMP;
	case texture_stage_arg_value::texture:
		return D3DTA_TEXTURE;
	default:
		throw exception("Invalid texture_stage_arg_value!");
	}
}

/*template<> D3DSAMPLERSTATETYPE sge::d3d9::convert_cast (const filter_arg& r)
{
	switch(r) {
	case FARG_MinFilter:
		return D3DSAMP_MINFILTER;
	case FARG_MagFilter:
		return D3DSAMP_MAGFILTER;
	case FARG_MipFilter:
		return D3DSAMP_MIPFILTER;
	default:
		throw std::logic_error("invalid filter_arg");
	}
}*/

/*template<> D3DTEXTUREFILTERTYPE sge::d3d9::convert_cast (const filter_value& r)
{
	switch(r) {
	//case FARGV_None:
	//	return D3DTEXF_NONE;
	case FV_Point:
		return D3DTEXF_POINT;
	case FV_Linear:
		return D3DTEXF_LINEAR;
	case FV_Anisotropic:
		return D3DTEXF_ANISOTROPIC;
	default:
		throw std::logic_error("invalid filter_arg_value");
	}
}*/

DWORD sge::d3d9::convert_lock_flags (const lock_flag_t lf, const resource_flag_t rf)
{
	DWORD l = 0;
	if((lf & lock_flags::discard) && (rf & resource_flags::dynamic))
		l |= D3DLOCK_DISCARD;
	return l;
}
