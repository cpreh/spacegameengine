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


#include <sge/renderer/renderer.hpp>

const sge::texture_ptr sge::renderer::no_texture;
const sge::texture_ptr sge::renderer::default_render_target;
const sge::glsl::program_ptr sge::renderer::no_program;

sge::screen_unit sge::renderer::screen_width() const
{
	return screen_size().w();
}

sge::screen_unit sge::renderer::screen_height() const
{
	return screen_size().h();
}

sge::space_unit sge::renderer::aspect() const
{
	return static_cast<space_unit>(screen_width())
	     / static_cast<space_unit>(screen_height());
}
