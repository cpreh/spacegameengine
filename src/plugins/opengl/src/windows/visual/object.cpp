/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/windows/visual/choose_and_set_format.hpp>
#include <sge/opengl/windows/visual/object.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/visual/object.hpp>


sge::opengl::windows::visual::object::object(
	sge::renderer::bit_depth::type const _bit_depth,
	sge::renderer::depth_stencil_buffer::type const _depth_stencil
)
:
	awl::backends::windows::visual::object(),
	bit_depth_(
		_bit_depth
	),
	depth_stencil_(
		_depth_stencil
	)
{
}

sge::opengl::windows::visual::object::~object()
{
}

void
sge::opengl::windows::visual::object::apply(
	HWND const _hwnd
) const
{
	sge::opengl::windows::visual::choose_and_set_format(
		_hwnd,
		bit_depth_,
		depth_stencil_
	);
}
