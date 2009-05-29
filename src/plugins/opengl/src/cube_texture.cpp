/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../texture_functions.hpp"
#include "../basic_texture_impl.hpp"
#include "../version.hpp"
#include "../enable.hpp"
#include "../texture.hpp"
#include "../glew.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/once.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/make_auto_ptr.hpp>
#include <sge/auto_ptr.hpp>
#include <boost/tr1/array.hpp>

namespace
{

void initialize_cube_texture();
GLenum cube_texture_type();
bool have_cube_texture();

GLenum
convert_cube_side(
	sge::renderer::cube_side::type const &s);

GLenum gl_cube_texture_type;
bool have_cube_texture_;

}

template class sge::ogl::basic_texture<sge::renderer::cube_texture>;

sge::ogl::cube_texture::cube_texture(
	size_type const sz,
	image::color::format::type const format,
	renderer::filter::texture const &filter,
	resource_flag_type const flags)
:
	detail::cube_texture_base(
		filter,
		flags,
		cube_texture_type(),
		format),
	sz(sz),
	locked_texture(0)
{
	if(!have_cube_texture())
		sge::ogl::on_not_supported(
			SGE_TEXT("cube texture"),
			SGE_TEXT("1.3"),
	       		SGE_TEXT("gl_arb_cube_texture"));

	for(
		unsigned i = 0;
		i < static_cast<unsigned>(
			sge::renderer::cube_side::num_elements);
		++i)
	{
		sge::auto_ptr<texture> p(
			make_auto_ptr<
				texture
			>(
				texture::dim_type(
					sz,
					sz),
				format,
				filter,
				flags,
				convert_cube_side(
					static_cast<renderer::cube_side::type>(i))
		));

		textures.push_back(
			p);
	}
}

sge::image::view::object const
sge::ogl::cube_texture::lock(
	renderer::cube_side::type const side,
	renderer::lock_rect const &src,
	lock_flag_type const flags)
{
	check_not_locked();

	locked_texture = &textures[side];
	return locked_texture->lock(
		src,
		flags);
}

sge::image::view::const_object const
sge::ogl::cube_texture::lock(
	renderer::cube_side::type const side,
	renderer::lock_rect const &src) const
{
	check_not_locked();

	locked_texture = &textures[side];
	return locked_texture->lock(
		src);
}

void sge::ogl::cube_texture::unlock() const
{
	check_locked();

	locked_texture->unlock();
	locked_texture = 0;
}

sge::ogl::cube_texture::size_type
sge::ogl::cube_texture::border_size() const
{
	return sz;
}

void sge::ogl::cube_texture::check_locked() const
{
	if(!locked_texture)
		throw exception(
			SGE_TEXT("ogl::cube_texture: not locked!"));
}

void sge::ogl::cube_texture::check_not_locked() const
{
	if(locked_texture)
		throw exception(
			SGE_TEXT("ogl::cube_texture: already locked!"));
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

	if(sge::ogl::glew_is_supported("GL_VERSION_1_3"))
		gl_cube_texture_type = GL_TEXTURE_CUBE_MAP;
	else if(sge::ogl::glew_is_supported("GL_ARB_texture_cube_map"))
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

typedef std::tr1::array<
	GLenum,
	sge::renderer::cube_side::num_elements
> cube_side_array;

cube_side_array const
normal_cube_sides = {{
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
}},
arb_cube_sides = {{
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
	GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB
}};

GLenum
convert_cube_side(
	sge::renderer::cube_side::type const &s)
{
	static const cube_side_array cube_sides
		= cube_texture_type() == GL_TEXTURE_CUBE_MAP
			? normal_cube_sides
			: arb_cube_sides;

	cube_side_array::size_type const pos
		= static_cast<
			cube_side_array::size_type
		>(s);

	if(pos >= cube_sides.size())
		throw sge::exception(
			SGE_TEXT("Invalid cube_side!"));

	return cube_sides[pos];
}


}
