/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CG_PARAMETER_ELEMENT_TYPE_HPP_INCLUDED
#define SGE_CG_PARAMETER_ELEMENT_TYPE_HPP_INCLUDED

#include <sge/cg/parameter/element_type_fwd.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{

enum class element_type
{
	double_,
	double1,
	double2,
	double3,
	double4,
	double1x1,
	double1x2,
	double1x3,
	double1x4,
	double2x1,
	double2x2,
	double2x3,
	double2x4,
	double3x1,
	double3x2,
	double3x3,
	double3x4,
	double4x1,
	double4x2,
	double4x3,
	double4x4,
	float_,
	float1,
	float2,
	float3,
	float4,
	float1x1,
	float1x2,
	float1x3,
	float1x4,
	float2x1,
	float2x2,
	float2x3,
	float2x4,
	float3x1,
	float3x2,
	float3x3,
	float3x4,
	float4x1,
	float4x2,
	float4x3,
	float4x4,
	int_,
	int1,
	int2,
	int3,
	int4,
	int1x1,
	int1x2,
	int1x3,
	int1x4,
	int2x1,
	int2x2,
	int2x3,
	int2x4,
	int3x1,
	int3x2,
	int3x3,
	int3x4,
	int4x1,
	int4x2,
	int4x3,
	int4x4
};

}
}
}

#endif
