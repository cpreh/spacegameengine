/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/sampler_color_arg_type.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/arg3.hpp>


GLenum
sge::opengl::state::convert::sampler_color_arg_type<
	sge::renderer::state::ffp::sampler::arg1
>::get()
{
	return GL_SRC0_RGB;
}

GLenum
sge::opengl::state::convert::sampler_color_arg_type<
	sge::renderer::state::ffp::sampler::arg2
>::get()
{
	return GL_SRC1_RGB;
}

GLenum
sge::opengl::state::convert::sampler_color_arg_type<
	sge::renderer::state::ffp::sampler::arg3
>::get()
{
	return GL_SRC2_RGB;
}
