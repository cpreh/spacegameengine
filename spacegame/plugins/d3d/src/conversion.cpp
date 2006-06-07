#include <stdexcept>
#include "../conversion.hpp"
#include "../../../core/renderer/renderer_types.hpp"

template<> DWORD sge::d3d::convert_cast (const lock_flag_t& r)
{
	DWORD l = 0;
	if(r & RF_Dynamic)
		l |= D3DUSAGE_DYNAMIC;
	if(r & RF_WriteOnly)
		l |= D3DUSAGE_WRITEONLY;
    return l;
}

template<> D3DPOOL sge::d3d::convert_cast (const resource_flag_t& r)
{
	if(r & RF_AutoRestore)
		return D3DPOOL_MANAGED;
	else
		return D3DPOOL_DEFAULT;
}

template<> D3DPRIMITIVETYPE sge::d3d::convert_cast (const primitive_type& r)
{
	switch(r) {
	case PT_Point:
		return D3DPT_POINTLIST;
	case PT_Line:
		return D3DPT_LINELIST;
	case PT_LineStrip:
		return D3DPT_LINESTRIP;
	case PT_Triangle:
		return D3DPT_TRIANGLELIST;
	case PT_TriangleStrip:
		return D3DPT_TRIANGLESTRIP;
	case PT_TriangleFan:
		return D3DPT_TRIANGLEFAN;
	default:
		throw std::logic_error("invalid primtype");
	}
}

template<> DWORD sge::d3d::convert_cast (const text_flags& r)
{
	DWORD l = 0;
	if(r & TXTF_AlignLeft)
		l |= DT_LEFT;
	if(r & TXTF_AlignHCenter)
		l |= DT_CENTER;
	if(r & TXTF_AlignRight)
		l |= DT_RIGHT;
	if(r & TXTF_AlignTop)
		l |= DT_TOP;
	if(r & TXTF_AlignVCenter)
		l |= DT_VCENTER;
	if(r & TXTF_AlignBottom)
		l |= DT_BOTTOM | DT_SINGLELINE;
	if(r & TXTF_NoMultiLine)
		l |= DT_SINGLELINE;
	return l;
}

template<> D3DMULTISAMPLE_TYPE sge::d3d::convert_cast (const multi_sample_type& r)
{
	switch(r) {
	case MS_None:
		return D3DMULTISAMPLE_NONE;
	case MS_2_Samples:
		return D3DMULTISAMPLE_2_SAMPLES;
	case MS_3_Samples:
		return D3DMULTISAMPLE_3_SAMPLES;
	case MS_4_Samples:
		return D3DMULTISAMPLE_4_SAMPLES;
	case MS_5_Samples:
		return D3DMULTISAMPLE_5_SAMPLES;
	case MS_6_Samples:
		return D3DMULTISAMPLE_6_SAMPLES;
	case MS_7_Samples:
		return D3DMULTISAMPLE_7_SAMPLES;
	case MS_8_Samples:
		return D3DMULTISAMPLE_8_SAMPLES;
	case MS_9_Samples:
		return D3DMULTISAMPLE_9_SAMPLES;
	case MS_10_Samples:
		return D3DMULTISAMPLE_10_SAMPLES;
	case MS_11_Samples:
		return D3DMULTISAMPLE_11_SAMPLES;
	case MS_12_Samples:
		return D3DMULTISAMPLE_12_SAMPLES;
	case MS_13_Samples:
		return D3DMULTISAMPLE_13_SAMPLES;
	case MS_14_Samples:
		return D3DMULTISAMPLE_14_SAMPLES;
	case MS_15_Samples:
		return D3DMULTISAMPLE_15_SAMPLES;
	case MS_16_Samples:
		return D3DMULTISAMPLE_16_SAMPLES;
	default:
		throw std::logic_error("invalid multi_sample_type");
	}
}

template<> D3DDECLUSAGE sge::d3d::convert_cast (const vertex_usage& r)
{
	switch(r) {
	case VU_Pos:
		return D3DDECLUSAGE_POSITION;
	case VU_Normal:
		return D3DDECLUSAGE_NORMAL;
	case VU_Tex:
		return D3DDECLUSAGE_TEXCOORD;
	case VU_Diffuse:
		return D3DDECLUSAGE_COLOR;
	default:
		throw std::logic_error("invalid vertex_usage");
	}
}

template<> D3DTRANSFORMSTATETYPE sge::d3d::convert_cast (const matrix_usage& r)
{
	switch(r) {
	case MU_Transform:
		return D3DTS_WORLD;
	case MU_Camera:
		return D3DTS_VIEW;
	case MU_Projection:
		return D3DTS_PROJECTION;
	default:
		throw std::logic_error("invalid matrix_usage");
	}
}

template<> D3DTEXTURESTAGESTATETYPE sge::d3d::convert_cast (const stage_op& r)
{
	switch(r) {
	case SOP_Color:
		return D3DTSS_COLOROP;
	case SOP_Alpha:
		return D3DTSS_ALPHAOP;
	default:
		throw std::logic_error("invalid stage_op");
	}
}

template<> D3DTEXTURESTAGESTATETYPE sge::d3d::convert_cast (const stage_arg& r)
{
	switch(r) {
	case SARG_Color1:
		return D3DTSS_COLORARG1;
	case SARG_Color2:
		return D3DTSS_COLORARG2;
	case SARG_Alpha1:
		return D3DTSS_ALPHAARG1;
	case SARG_Alpha2:
		return D3DTSS_ALPHAARG2;
	default:
		throw std::logic_error("invalid stage_arg");
	}
}

template<> DWORD sge::d3d::convert_cast (const stage_op_value& r)
{
	switch(r) {
	case SOPV_Disable:
		return D3DTOP_DISABLE;
	case SOPV_SelectArg1:
		return D3DTOP_SELECTARG1;
	case SOPV_SelectArg2:
		return D3DTOP_SELECTARG2;
	case SOPV_Modulate:
		return D3DTOP_MODULATE;
	case SOPV_Modulate2X:
		return D3DTOP_MODULATE2X;
	case SOPV_Modulate4X:
		return D3DTOP_MODULATE4X;
	case SOPV_Add:
		return D3DTOP_ADD;
	case SOPV_AddSigned:
		return D3DTOP_ADDSIGNED;
	case SOPV_AddSigned2X:
		return D3DTOP_ADDSIGNED2X;
	case SOPV_Subtract:
		return D3DTOP_SUBTRACT;
	case SOPV_AddSmooth:
		return D3DTOP_ADDSMOOTH;
	case SOPV_BlendDiffuseAlpha:
		return D3DTOP_BLENDDIFFUSEALPHA;
	case SOPV_BlendTextureAlpha:
		return D3DTOP_BLENDTEXTUREALPHA;
	case SOPV_BlendFactorAlpha:
		return D3DTOP_BLENDFACTORALPHA;
	case SOPV_BlendTextureAlphaPM:
		return D3DTOP_BLENDTEXTUREALPHAPM;
	case SOPV_BlendCurrentAlpha:
		return D3DTOP_BLENDCURRENTALPHA;
	case SOPV_PreModulate:
		return D3DTOP_PREMODULATE;
	case SOPV_ModulateAlphaAddColor:
		return D3DTOP_MODULATEALPHA_ADDCOLOR;
	case SOPV_ModulateColorAddAlpha:
		return D3DTOP_MODULATECOLOR_ADDALPHA;
	case SOPV_ModulateInvAlphaAddColor:
		return D3DTOP_MODULATEINVALPHA_ADDCOLOR;
	case SOPV_ModulateInvColorAddAlpha:
		return D3DTOP_MODULATEINVCOLOR_ADDALPHA;
	case SOPV_BumpenvMap:
		return D3DTOP_BUMPENVMAP;
	case SOPV_BumpenvMapLuminance:
		return D3DTOP_BUMPENVMAPLUMINANCE;
	case SOPV_DotProduct3:
		return D3DTOP_DOTPRODUCT3;
	case SOPV_MultiplyAdd:
		return D3DTOP_MULTIPLYADD;
	case SOPV_Lerp:
		return D3DTOP_LERP;
	default:
		throw std::logic_error("invalid stage_op_value");
	}
}

template<> DWORD sge::d3d::convert_cast (const stage_arg_value& r)
{
	switch(r) {
	case SARGV_Constant:
		return D3DTA_CONSTANT;
	case SARGV_Current:
		return D3DTA_CURRENT;
	case SARGV_Diffuse:
		return D3DTA_DIFFUSE;
	case SARGV_Specular:
		return D3DTA_SPECULAR;
	case SARGV_Temp:
		return D3DTA_TEMP;
	case SARGV_Texture:
		return D3DTA_TEXTURE;
	default:
		throw std::logic_error("invalid stage_arg_value");
	}
}

template<> D3DSAMPLERSTATETYPE sge::d3d::convert_cast (const filter_arg& r)
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
}

template<> D3DTEXTUREFILTERTYPE sge::d3d::convert_cast (const filter_arg_value& r)
{
	switch(r) {
	case FARGV_None:
		return D3DTEXF_NONE;
	case FARGV_Point:
		return D3DTEXF_POINT;
	case FARGV_Linear:
		return D3DTEXF_LINEAR;
	case FARGV_Anisotropic:
		return D3DTEXF_ANISOTROPIC;
	default:
		throw std::logic_error("invalid filter_arg_value");
	}
}

DWORD sge::d3d::convert_lock_flags (const lock_flag_t lf, const resource_flag_t rf)
{
	DWORD l = 0;
	if(lf & LF_Discard && rf & RF_Dynamic)
		l |= D3DLOCK_DISCARD;
	return l;
}
