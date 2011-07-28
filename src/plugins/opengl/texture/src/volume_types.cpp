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


#include "../volume_types.hpp"
#include "../funcs/set_3d.hpp"
#include "../funcs/set_box.hpp"
#include <fcppt/text.hpp>

sge::renderer::size_type
sge::opengl::texture::volume_types::min_size()
{
	return 16u;
}

fcppt::string
sge::opengl::texture::volume_types::name()
{
	return FCPPT_TEXT("volume texture");
}

sge::opengl::texture::volume_types::init_function_type
sge::opengl::texture::volume_types::init_function()
{
	return &texture::funcs::set_3d;
}

sge::opengl::texture::volume_types::sub_function_type
sge::opengl::texture::volume_types::sub_function()
{
	return &texture::funcs::set_box;
}
