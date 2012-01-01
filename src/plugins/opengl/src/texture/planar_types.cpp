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


#include <sge/opengl/texture/planar_types.hpp>
#include <sge/opengl/texture/funcs/set_2d.hpp>
#include <sge/opengl/texture/funcs/set_rect.hpp>
#include <fcppt/text.hpp>

sge::renderer::size_type
sge::opengl::texture::planar_types::min_size()
{
	return 64u;
}

fcppt::string
sge::opengl::texture::planar_types::name()
{
	return FCPPT_TEXT("planar texture");
}

sge::opengl::texture::planar_types::init_function_type
sge::opengl::texture::planar_types::init_function()
{
	return &texture::funcs::set_2d;
}

sge::opengl::texture::planar_types::sub_function_type
sge::opengl::texture::planar_types::sub_function()
{
	return &texture::funcs::set_rect;
}
