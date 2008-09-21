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


#include "../split_states.hpp"
#include "../common.hpp"
#include "../error.hpp"
#include "../conversion.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::split_states::split_states(
	renderer::state_list &states)
: states(states)
{}

void sge::ogl::split_states::update_stencil()
{
	SGE_OPENGL_SENTRY

	glStencilFunc(
		convert_cast(
			states.get<renderer::stencil_func::type>()),
		0, // FIXME
		0); // FIXME
}

void sge::ogl::split_states::update_blend()
{
	SGE_OPENGL_SENTRY

	glBlendFunc(
		convert_cast(
			states.get<renderer::source_blend_func::type>()),
		convert_cast(
			states.get<renderer::dest_blend_func::type>()));
}

void sge::ogl::split_states::update_alpha_test()
{
	SGE_OPENGL_SENTRY	
}
