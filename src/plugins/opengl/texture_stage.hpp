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


#ifndef SGE_OPENGL_TEXTURE_STAGE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_STAGE_HPP_INCLUDED

#include "common.hpp"
#include "multi_texture.hpp"
#include "conversion.hpp"

namespace sge
{
namespace ogl
{

void tex_envf_ext(GLenum arg, GLenum value);

void set_texture_stage_scale(texture_stage_op_value::type value);

template<typename Arg, typename Value>
void set_texture_stage(const stage_type stage, const Arg arg, const Value value)
{
	set_texture_level(stage);
	const GLenum glarg = convert_cast(arg),
	             glvalue = convert_cast(value);

	tex_envf_ext(glarg, glvalue);
}

}
}

#endif
