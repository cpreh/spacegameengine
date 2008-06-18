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


#include <sge/renderer/device.hpp>

const sge::renderer::texture_ptr sge::renderer::device::no_texture;
const sge::renderer::texture_ptr sge::renderer::device::default_render_target;
const sge::renderer::glsl::program_ptr sge::renderer::device::no_program;

sge::renderer::screen_unit
sge::renderer::device::screen_width() const
{
	return screen_size().w();
}

sge::renderer::screen_unit
sge::renderer::device::screen_height() const
{
	return screen_size().h();
}

sge::space_unit
sge::renderer::device::aspect() const
{
	return static_cast<space_unit>(screen_width())
	     / static_cast<space_unit>(screen_height());
}

sge::renderer::device::~device()
{}
