/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_CONVERT_STATES_HPP_INCLUDED
#define SGE_OPENGL_CONVERT_STATES_HPP_INCLUDED

#include "common.hpp"
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/alpha_func.hpp>
#include <sge/renderer/state/fog_mode.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>

// TODO: split this!

namespace sge
{
namespace ogl
{

GLenum
convert_states(
	renderer::state::bool_::type);

GLenum
convert_states(
	renderer::state::cull_mode::type);

GLenum
convert_states(
	renderer::state::depth_func::type);

GLenum 
convert_states(
	renderer::state::stencil_func::type);

GLenum
convert_states(
	renderer::state::alpha_func::type);

GLenum
convert_states(
	renderer::state::fog_mode::type);

GLenum
convert_states(
	renderer::state::source_blend_func::type);

GLenum
convert_states(
	renderer::state::dest_blend_func::type);

GLenum
convert_states(
	renderer::state::draw_mode::type);


}
}

#endif
