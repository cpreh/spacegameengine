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


#ifndef SGE_OPENGL_CONVERSION_HPP_INCLUDED
#define SGE_OPENGL_CONVERSION_HPP_INCLUDED

#include "common.hpp"
#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/texture_filter.hpp>

namespace sge
{
namespace ogl
{

// TODO: put some of them in their appropriate locations

GLenum convert_cast(renderer::bool_state::type);
GLenum convert_cast(renderer::cull_mode::type);
GLenum convert_cast(renderer::depth_func::type);
GLenum convert_cast(renderer::stencil_func::type);
GLenum convert_cast(renderer::alpha_func::type);
GLenum convert_cast(renderer::fog_mode::type);
GLenum convert_cast(renderer::source_blend_func::type);
GLenum convert_cast(renderer::dest_blend_func::type);
GLenum convert_cast(renderer::draw_mode::type);

GLenum convert_cast(const renderer::indexed_primitive_type::type&);
GLenum convert_cast(const renderer::nonindexed_primitive_type::type&);
GLenum convert_cast(const renderer::min_filter::type&);
GLenum convert_cast(const renderer::mag_filter::type&);
GLenum convert_cast(const renderer::texture_stage_op::type&);
GLenum convert_cast(const renderer::texture_stage_op_value::type&);
GLenum convert_cast(const renderer::texture_stage_arg::type&);
GLenum convert_cast(const renderer::texture_stage_arg_value::type&);

GLuint convert_resource_flags(renderer::resource_flag_t);
GLenum convert_fog_float_state(renderer::float_state::type);
GLenum convert_clear_bit(renderer::bool_state::type);

}
}

#endif
