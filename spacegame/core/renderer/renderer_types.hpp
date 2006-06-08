#ifndef SGE_RENDERERTYPES_HPP_INCLUDED
#define SGE_RENDERERTYPES_HPP_INCLUDED

#include <vector>
#include <stdexcept>
#include "../main/types.hpp"
#include "../main/window.hpp"
#include "../math/vector2.hpp"
#include "../math/vector3.hpp"
#include "../math/vector4.hpp"
#include "../math/matrix4x4.hpp"
#include "../math/quaternion.hpp"

namespace sge
{
	typedef uint32 color;

	#define RGBA_MAKRO(r,g,b,a) color(color(a) << 24 | color(r) << 16 | color(g) << 8 | color(b))

	template<uchar r, uchar g, uchar b, uchar a> struct static_rgba {
		static const color value = RGBA_MAKRO(r,g,b,a);
	};

	template<uchar r, uchar g, uchar b> struct static_rgb {
		static const color value = RGBA_MAKRO(r,g,b,255);
	};

	inline color rgba(const uchar r, const uchar g, const uchar b, const uchar a)
	{
		return RGBA_MAKRO(r,g,b,a);
	}

	inline float   red_part_rgba_f(const color c) { return ((c & 0xFF000000) >> 24) / 255.f; }
	inline float green_part_rgba_f(const color c) { return ((c &   0xFF0000) >> 16) / 255.f; }
	inline float  blue_part_rgba_f(const color c) { return ((c &     0xFF00) >>  8) / 255.f; }
	inline float alpha_part_rgba_f(const color c) { return  (c &       0xFF)        / 255.f; }
	
	struct colors {
		static const color black  = static_rgb<  0,  0,  0>::value,
		                   white  = static_rgb<255,255,255>::value,
				   red    = static_rgb<255,  0,  0>::value,
				   green  = static_rgb<  0,255,  0>::value,
				   blue   = static_rgb<  0,  0,255>::value,
				   yellow = static_rgb<  0,255,255>::value,
				   purple = static_rgb<255,  0,255>::value,
				   orange = static_rgb<255,255,  0>::value,
		                   transparent = static_rgba<0,0,0,0>::value;
	};

	enum bit_depth {
		BD_16,
		BD_32
	};
	inline unsigned bit_depth_bit_count(const bit_depth d) { return d == BD_32 ? 32 : 16; }

	struct display_mode {
		display_mode(const unsigned width, const unsigned height, const bit_depth depth,
			     const unsigned refresh_rate)
			: width(width), height(height), depth(depth),
			  refresh_rate(refresh_rate) {}
		unsigned  width;
		unsigned  height;
		bit_depth depth;
		unsigned  refresh_rate;
	};

	inline bool operator== (const display_mode& l, const display_mode& r)
	{
		return l.depth == r.depth && l.width == r.width && l.height == r.height && l.refresh_rate == r.refresh_rate;
	}

	inline bool operator!= (const display_mode& l, const display_mode& r)
	{
		return !(l==r);
	}

	typedef unsigned multi_sample_type;

	struct renderer_parameters {
		renderer_parameters(const display_mode& mode, 
				    const multi_sample_type samples = 1,
				    const bool windowed = false,
				    const bool vsync = true)
		: mode(mode), samples(samples),
		  windowed(windowed), vsync(vsync) {}
		display_mode      mode;
		multi_sample_type samples;
		bool              windowed;
		bool              vsync;
	};

	inline bool operator== (const renderer_parameters& l, const renderer_parameters& r)
	{
		return l.mode == r.mode && l.samples == r.samples && l.windowed == r.windowed && l.vsync == r.vsync;
	}

	inline bool operator!= (const renderer_parameters& l, const renderer_parameters& r)
	{
		return !(l==r);
	}

	typedef std::vector<display_mode> display_mode_array;
	struct renderer_caps {
		int adapter_number;
		std::string driver_name;
		std::string description;
		display_mode_array display_modes;
		unsigned max_tex_width;
		unsigned max_tex_height;
	};

	struct color4 {
		typedef space_unit value_type;
		color4(const value_type a = 0, const value_type r = 0, const value_type g = 0, const value_type b = 0)
		: a(a), r(r), g(g), b(b) {}
	
		value_type a,r,g,b;
	};

	inline bool operator==(const color4& l, const color4& r)
	{
		return l.a == r.a && l.r == r.r && l.g == r.g && l.b == r.b;
	}

	inline bool operator!=(const color4& l, const color4& r)
	{
		return !(l==r);
	}

	enum resource_flags {
		RF_Dynamic     = 1,
		RF_WriteOnly   = 1 << 1,
		RF_AutoRestore = 1 << 2,
		RF_Default     = RF_WriteOnly,
		RF_num_elements
	};
	typedef unsigned resource_flag_t;

	enum lock_flags {
		LF_Default,
		LF_Discard
	};
	typedef unsigned lock_flag_t;

	typedef vector2<space_unit>    tex_pos;
	typedef vector3<space_unit>    pos3;
	typedef vector2<space_unit>    point;
	typedef uint32                 int_type;
	typedef space_unit             float_type;
	typedef bool                   bool_type;

	enum primitive_type {
		PT_Point,
		PT_Line,
		PT_LineStrip,
		PT_Triangle,
		PT_TriangleStrip,
		PT_TriangleFan
	};

	enum int_state {
		IS_ClearColor,
		IS_AmbientLightColor,
		IS_FogColor,
		IS_StencilClearVal,
		IS_FogMode
	};

	enum float_state {
		FS_ZBufferClearVal,
		FS_FogStart,
		FS_FogEnd,
		FS_FogDensity
	};

	enum bool_state {
		BS_ClearZBuffer,
		BS_ClearBackBuffer,
		BS_ClearStencil,
		BS_EnableFog,
		BS_EnableRangeFog,
		BS_EnableStencil,
		BS_EnableAlphaBlending,
		BS_EnableZBuffer
	};

	enum stage_op {
		SOP_Color,
		SOP_Alpha
	};

	enum stage_op_value {
		SOPV_Disable,
		SOPV_SelectArg1,
		SOPV_SelectArg2,
		SOPV_Modulate,
		SOPV_Modulate2X,
		SOPV_Modulate4X,
		SOPV_Add,
		SOPV_AddSigned,
		SOPV_AddSigned2X,
		SOPV_Subtract,
		SOPV_AddSmooth,
		SOPV_BlendDiffuseAlpha,
		SOPV_BlendTextureAlpha,
		SOPV_BlendFactorAlpha,
		SOPV_BlendTextureAlphaPM,
		SOPV_BlendCurrentAlpha,
		SOPV_PreModulate,
		SOPV_ModulateAlphaAddColor,
		SOPV_ModulateColorAddAlpha,
		SOPV_ModulateInvAlphaAddColor,
		SOPV_ModulateInvColorAddAlpha,
		SOPV_BumpenvMap,
		SOPV_BumpenvMapLuminance,
		SOPV_DotProduct3,
		SOPV_MultiplyAdd,
		SOPV_Lerp
	};

	enum stage_arg {
		SARG_Color1,
		SARG_Color2,
		SARG_Alpha1,
		SARG_Alpha2
	};

	enum stage_arg_value {
		SARGV_Constant,
		SARGV_Current,
		SARGV_Diffuse,
		SARGV_Specular,
		SARGV_Temp,
		SARGV_Texture
	};

	enum filter_arg {
		FARG_MinFilter,
		FARG_MagFilter,
		FARG_MipFilter
	};

	enum filter_arg_value {
		FARGV_None,
		FARGV_Point,
		FARGV_Linear,
		FARGV_Anisotropic
	};

	class stage_type {
	public:
		typedef unsigned value_type;
		static const value_type max_stage = 4;

		stage_type(const value_type i) : stage(i) { check(); }
		stage_type& operator=(const value_type& v)
		{
			stage = v;
			check();
			return *this;
		}
		operator value_type() const { return stage; }
	private:
		void check() const
		{
			if(stage >= max_stage)
				throw std::range_error("stage_type must be in [0;MAX_STAGE)!");
		}
		value_type stage;
	};

	struct view_port {
		typedef vector2<space_unit> pos_type;
		pos_type     pos;
		pos_type     sz;
		space_unit   nearz;
		space_unit   farz;
		view_port(const space_unit x, const space_unit y, const space_unit w, const space_unit h, const space_unit nearz, const space_unit farz)
			: pos(x,y), sz(w,h), nearz(nearz), farz(farz) {}
	};

	struct material {
		material(const color4 diffuse = color4(), const color4 ambient = color4(),
		         const color4 specular = color4(), const color4 emissive = color4(),
		         const space_unit power = 0)
			: diffuse(diffuse), ambient(ambient), specular(specular),
			  emissive(emissive), power(power) {}
			color4     diffuse;
			color4     ambient; 
			color4     specular; 
			color4     emissive; 
			space_unit power; 
	};

	enum matrix_usage {
		MU_Transform,
		MU_Camera,
		MU_Projection
	};
}

#endif
