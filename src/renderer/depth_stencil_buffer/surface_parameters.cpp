/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/ds/format.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters.hpp>


sge::renderer::depth_stencil_buffer::surface_parameters::surface_parameters(
	sge::renderer::dim2 const &_size,
	sge::image::ds::format const _format
)
:
	size_(
		_size
	),
	format_(
		_format
	)
{
}

sge::renderer::dim2 const &
sge::renderer::depth_stencil_buffer::surface_parameters::size() const
{
	return size_;
}

sge::image::ds::format
sge::renderer::depth_stencil_buffer::surface_parameters::format() const
{
	return format_;
}
