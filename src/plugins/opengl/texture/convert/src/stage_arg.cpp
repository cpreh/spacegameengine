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


#include "../stage_arg.hpp"
#include "../../../common.hpp"
#include <sge/renderer/sampler_stage_arg.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::texture::convert::stage_arg_op(
	renderer::sampler_stage_arg::type const _arg
)
{
	switch(
		_arg
	)
	{
	case renderer::sampler_stage_arg::rgb0:
		return GL_SOURCE0_RGB;
	case renderer::sampler_stage_arg::rgb1:
		return GL_SOURCE1_RGB;
	case renderer::sampler_stage_arg::rgb2:
		return GL_SOURCE2_RGB;
	case renderer::sampler_stage_arg::alpha0:
		return GL_SOURCE0_ALPHA;
	case renderer::sampler_stage_arg::alpha1:
		return GL_SOURCE1_ALPHA;
	case renderer::sampler_stage_arg::alpha2:
		return GL_SOURCE2_ALPHA;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
