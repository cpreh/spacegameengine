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


#include <sge/renderer/clear/back_buffer_value.hpp>
#include <sge/renderer/clear/depth_buffer_value.hpp>
#include <sge/renderer/clear/optional_back_buffer.hpp>
#include <sge/renderer/clear/optional_depth_buffer.hpp>
#include <sge/renderer/clear/optional_stencil_buffer.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/clear/stencil_buffer_value.hpp>


sge::renderer::clear::parameters::parameters()
:
	back_buffer_(),
	depth_buffer_(),
	stencil_buffer_()
{
}

sge::renderer::clear::parameters &
sge::renderer::clear::parameters::back_buffer(
	sge::renderer::clear::back_buffer_value const &_back_buffer
)
{
	back_buffer_ =
		sge::renderer::clear::optional_back_buffer(
			_back_buffer
		);

	return
		*this;
}

sge::renderer::clear::parameters &
sge::renderer::clear::parameters::depth_buffer(
	sge::renderer::clear::depth_buffer_value const _depth_buffer
)
{
	depth_buffer_ =
		sge::renderer::clear::optional_depth_buffer(
			_depth_buffer
		);

	return
		*this;
}

sge::renderer::clear::parameters &
sge::renderer::clear::parameters::stencil_buffer(
	sge::renderer::clear::stencil_buffer_value const _stencil_buffer
)
{
	stencil_buffer_ =
		sge::renderer::clear::optional_stencil_buffer(
			_stencil_buffer
		);

	return
		*this;
}

sge::renderer::clear::optional_back_buffer const &
sge::renderer::clear::parameters::back_buffer() const
{
	return
		back_buffer_;
}

sge::renderer::clear::optional_depth_buffer const &
sge::renderer::clear::parameters::depth_buffer() const
{
	return
		depth_buffer_;
}

sge::renderer::clear::optional_stencil_buffer const &
sge::renderer::clear::parameters::stencil_buffer() const
{
	return
		stencil_buffer_;
}
