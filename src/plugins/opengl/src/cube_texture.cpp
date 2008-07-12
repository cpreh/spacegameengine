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


#include "../common.hpp"
#include "../cube_texture.hpp"
#include "../conversion.hpp"
#include "../error.hpp"
#include "../texture_functions.hpp"
#include "../basic_texture_impl.hpp"
#include "../version.hpp"
#include "../enable.hpp"
#include <sge/renderer/scoped_lock.hpp>
#include <sge/once.hpp>
#include <boost/assign/list_of.hpp>
#include <algorithm>

namespace
{

void initialize_cube_texture();
GLenum cube_texture_type();
bool have_cube_texture();

GLenum gl_cube_texture_type;
bool have_cube_texture_;

}

template class sge::ogl::basic_texture<sge::renderer::cube_texture>;

sge::ogl::cube_texture::cube_texture(
	image_view_6 const &src,
	renderer::filter_args const &filter,
	const resource_flag_type flags)
 : detail::cube_texture_base(filter, flags, cube_texture_type()),
  sz(0)
{
	if(!have_cube_texture())
		sge::ogl::on_not_supported(
			SGE_TEXT("cube texture"),
			SGE_TEXT("1.3"),
	       		SGE_TEXT("gl_arb_cube_texture"));

	//if(src)
	//	renderer::cube_texture::set_data(*src);
}

sge::ogl::cube_texture::size_type
sge::ogl::cube_texture::border_size() const
{
	return sz;
}

void sge::ogl::cube_texture::do_sub_data(
	const renderer::cube_side::type side,
	renderer::image_view const &,
	renderer::lock_rect const &r)
{
/*	pre_setdata();
	//scoped_lock<sge::cube_texture*> lock_(this, lock_flags::writeonly);
	//std::copy(src, src + size(), data());
	set_texture_rect(
		convert_cast(side),
		filter(),
		renderer::texture::dim_type(
			border_size(),
			border_size()),
		r,
		src);*/
}

void sge::ogl::cube_texture::data(
	const renderer::cube_side::type side,
	renderer::image_view const &)
{
/*	pre_setdata();
	set_texture(
		convert_cast(side),
		filter(),
		renderer::texture::dim_type(
			border_size(),
			border_size()),
		src);*/
}

void sge::ogl::cube_texture::lock(
	renderer::cube_side::type const side,
	lock_flag_type const lmode)
{
	
}

void sge::ogl::cube_texture::lock(
	renderer::cube_side::type const side,
	renderer::lock_rect const &src,
	lock_flag_type const flags)
{

}

void sge::ogl::cube_texture::unlock()
{
}

sge::renderer::image_view const
sge::ogl::cube_texture::view()
{
}

sge::renderer::const_image_view const
sge::ogl::cube_texture::view() const
{
}

GLenum sge::ogl::convert_cast(const renderer::cube_side::type& s)
{
	typedef boost::array<GLenum, sge::renderer::cube_side::num_elements> cube_side_array;
	static const cube_side_array cube_sides = cube_texture_type() == GL_TEXTURE_CUBE_MAP
		? boost::assign::list_of
			(GL_TEXTURE_CUBE_MAP_POSITIVE_Z)
			(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
			(GL_TEXTURE_CUBE_MAP_NEGATIVE_X)
			(GL_TEXTURE_CUBE_MAP_POSITIVE_X)
			(GL_TEXTURE_CUBE_MAP_POSITIVE_Y)
			(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)
		: boost::assign::list_of
			(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB)
			(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB)
			(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB)
			(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB)
			(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB)
			(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB);


	const cube_side_array::size_type pos = static_cast<cube_side_array::size_type>(s);
	if(pos >= cube_sides.size())
		throw exception(SGE_TEXT("Invalid cube_side!"));

	return cube_sides[pos];
}

void sge::ogl::disable_cube_texture()
{
	if(have_cube_texture())
		disable(cube_texture_type());
}

namespace
{

void initialize_cube_texture()
{
	SGE_FUNCTION_ONCE

	if(GLEW_VERSION_1_3)
		gl_cube_texture_type = GL_TEXTURE_CUBE_MAP;
	else if(GLEW_ARB_texture_cube_map)
		gl_cube_texture_type = GL_TEXTURE_CUBE_MAP_ARB;
	else
		return;
	have_cube_texture_ = true;
}

GLenum cube_texture_type()
{
	initialize_cube_texture();
	return gl_cube_texture_type;
}

bool have_cube_texture()
{
	initialize_cube_texture();
	return have_cube_texture_;
}

}
