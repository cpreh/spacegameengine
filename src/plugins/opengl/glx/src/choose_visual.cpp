/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../choose_visual.hpp"
#include "../handle_bit_depth.hpp"
#include <GL/glx.h>
#include <sge/renderer/no_multi_sampling.hpp>
#include <fcppt/container/raw_vector_impl.hpp>

sge::opengl::glx::visual_attribute_array const
sge::opengl::glx::choose_visual(
	renderer::bit_depth::type const bit_depth,
	renderer::depth_buffer::type const depth_buffer,
	renderer::stencil_buffer::type const stencil_buffer,
	renderer::multi_sample_type const multi_samples
)
{
	visual_attribute_array ret;
	ret.push_back(GLX_RGBA);
	ret.push_back(GLX_DOUBLEBUFFER);

	glx::handle_bit_depth(
		ret,
		bit_depth
	);

	if(depth_buffer != renderer::depth_buffer::off)
	{
		ret.push_back(GLX_DEPTH_SIZE);
		ret.push_back(static_cast<int>(depth_buffer)); // TODO
	}

	if(stencil_buffer != renderer::stencil_buffer::off)
	{
		ret.push_back(GLX_STENCIL_SIZE);
		ret.push_back(static_cast<int>(stencil_buffer)); // TODO
	}

	// note: create_window is called before glew can be initialized, so we can't ask it here
	// if we have multi sample support
	if(multi_samples != renderer::no_multi_sampling)
	{
		ret.push_back(GLX_SAMPLES);
		ret.push_back(static_cast<int>(multi_samples));
	}

	ret.push_back(None);
	return ret;
}
