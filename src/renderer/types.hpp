/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_RENDERER_TYPES_HPP_INCLUDED
#define SGE_RENDERER_TYPES_HPP_INCLUDED

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <ostream>
#include "../types.hpp"
#include "../math/vector.hpp"
#include "../math/dim.hpp"
#include "color.hpp"

namespace sge
{

enum bit_depth {
	BD_16,
	BD_32
};

inline unsigned bit_depth_bit_count(const bit_depth d)
{
	return d == BD_32 ? 32 : 16;
}

typedef int pixel_unit;
typedef unsigned screen_unit;
typedef math::vector<pixel_unit,2> pixel_pos_t;
typedef math::dim<screen_unit,2> screen_size_t;

struct display_mode {
	display_mode(const screen_unit width, const screen_unit height, const bit_depth depth, const unsigned refresh_rate = 0);
	
	screen_size_t size;
	bit_depth depth;
	unsigned refresh_rate;

	screen_unit width() const;
	screen_unit height() const;
};

std::ostream& operator<< (std::ostream& s, const display_mode& mode);

inline bool operator== (const display_mode& l, const display_mode& r)
{
	return l.depth == r.depth && l.size == r.size && l.refresh_rate == r.refresh_rate;
}

inline bool operator!= (const display_mode& l, const display_mode& r)
{
	return !(l==r);
}

typedef unsigned multi_sample_type;

struct renderer_parameters {
	renderer_parameters(const display_mode& mode, const bool windowed = false, const multi_sample_type samples = 1, const bool vsync = true)
	: mode(mode), samples(samples), windowed(windowed), vsync(vsync) {}

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
	unsigned adapter_number;
	std::string driver_name;
	std::string description;
	display_mode_array display_modes;
	unsigned max_tex_size;
};

enum resource_flags {
	RF_None,
	RF_Dynamic     = 1,
	RF_WriteOnly   = 1 << 1,
	RF_Default     = RF_WriteOnly,
	RF_num_elements
};
typedef unsigned resource_flag_t;

enum lock_flags {
	LF_Default,
	LF_Discard
};
typedef unsigned lock_flag_t;

typedef math::vector2  tex_pos;
typedef math::vector3  pos3;
typedef uint32         int_type;
typedef space_unit     float_type;
typedef bool           bool_type;

enum indexed_primitive_type {
	PT_Line,
	PT_Triangle
};

enum nonindexed_primitive_type {
	PT_Point,
	PT_LineStrip,
	PT_LineLoop,
	PT_TriangleStrip,
	PT_TriangleFan
};

enum int_state {
	IS_ClearColor,
	IS_StencilClearVal,
	IS_DepthClearVal,
	IS_AmbientLightColor,
	IS_FogColor,
	IS_FogMode
};

enum fog_mode {
	FM_Linear,
	FM_Exp,
	FM_Exp2
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
	BS_EnableStencil,
	BS_EnableAlphaBlending,
	BS_EnableZBuffer,
	BS_EnableLighting,
	BS_EnableCulling
};

enum stage_op {
	SOP_Color,
	SOP_Alpha
};

enum cull_mode {
	CM_Back,
	CM_Front
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

enum filter_value {
	FV_Point,
	FV_Linear,
	FV_MipMap,
	FV_Anisotropic
};

struct filter_args {
	filter_args(const filter_value min_filter, const filter_value mag_filter)
	 : min_filter(min_filter),
	   mag_filter(mag_filter)
	{}

	filter_value min_filter,
	             mag_filter;
};

const filter_args linear_filter(FV_Linear, FV_Linear),
                  point_filter(FV_Point, FV_Point);

typedef std::size_t stage_type;

struct viewport {
	screen_unit x, y, w, h;

	viewport(const screen_unit x, const screen_unit y, const screen_unit w, const screen_unit h)
	 : x(x), y(y), w(w), h(h)
	{}
};

struct material {
	material(const color4 diffuse = color4(), const color4 ambient = color4(),
	         const color4 specular = color4(), const color4 emissive = color4(),
	         const space_unit power = 0)
	 : diffuse(diffuse), ambient(ambient), specular(specular), emissive(emissive), power(power) {}
	color4     diffuse;
	color4     ambient; 
	color4     specular; 
	color4     emissive; 
	space_unit power; 
};

enum cube_side {
	CS_Front,
	CS_Back,
	CS_Left,
	CS_Right,
	CS_Top,
	CS_Bottom,
	CS_num_elements
};

}

#endif
