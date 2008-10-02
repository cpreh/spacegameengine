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


#include <sge/renderer/parameters.hpp>

sge::renderer::parameters::parameters(
	display_mode const &mode_,
	depth_buffer::type const depth_buffer_,
	stencil_buffer::type const stencil_buffer_,
	window_mode::type const window_mode_,
	vsync::type const vsync_,
	multi_sample_type const samples_)
:
	mode_(mode_),
	depth_buffer_(depth_buffer_),
	stencil_buffer_(stencil_buffer_),
	window_mode_(window_mode_),
	vsync_(vsync_),
	samples_(samples_)
{}

sge::renderer::display_mode const &
sge::renderer::parameters::mode() const
{
	return mode_;
}

sge::renderer::depth_buffer::type
sge::renderer::parameters::dbuffer() const
{
	return depth_buffer_;
}

sge::renderer::stencil_buffer::type
sge::renderer::parameters::sbuffer() const
{
	return stencil_buffer_;
}

sge::renderer::window_mode::type
sge::renderer::parameters::wmode() const
{
	return window_mode_;
}

sge::renderer::vsync::type
sge::renderer::parameters::vsmode() const
{
	return vsync_;
}

sge::renderer::multi_sample_type
sge::renderer::parameters::samples() const
{
	return samples_;
}
