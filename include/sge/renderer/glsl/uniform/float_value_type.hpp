/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_GLSL_UNIFORM_FLOAT_VALUE_TYPE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_FLOAT_VALUE_TYPE_HPP_INCLUDED

namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

/**
\brief The namespace for the float_value_type enum
*/
namespace float_value_type
{
/**
\brief The enum type for float value types
*/
enum type
{
	/**
	\brief Each array element consists of 1 float
	*/
	float1,
	/**
	\brief Each array element consists of 2 floats
	*/
	float2,
	/**
	\brief Each array element consists of 3 floats
	*/
	float3,
	/**
	\brief Each array element consists of 4 floats
	*/
	float4,
	/**
	\brief Each array element consists of 2x2 matrix of floats
	*/
	matrix2x2,
	/**
	\brief Each array element consists of 3x3 matrix of floats
	*/
	matrix3x3,
	/**
	\brief Each array element consists of 4x4 matrix of floats
	*/
	matrix4x4,
	/**
	\brief Each array element consists of 2x3 matrix of floats
	*/
	matrix2x3,
	/**
	\brief Each array element consists of 3x2 matrix of floats
	*/
	matrix3x2,
	/**
	\brief Each array element consists of 2x4 matrix of floats
	*/
	matrix2x4,
	/**
	\brief Each array element consists of 4x2 matrix of floats
	*/
	matrix4x2,
	/**
	\brief Each array element consists of 3x4 matrix of floats
	*/
	matrix3x4,
	/**
	\brief Each array element consists of 4x3 matrix of floats
	*/
	matrix4x3
};
}

}
}
}
}

#endif
