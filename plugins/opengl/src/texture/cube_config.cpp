//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/cube_config.hpp>
#include <sge/opengl/texture/cube_side_array.hpp>
#include <sge/opengl/texture/type.hpp>


sge::opengl::texture::cube_config::cube_config(
	sge::opengl::texture::type const _cube_texture_type,
	sge::opengl::texture::cube_side_array const &_cube_sides
)
:
	cube_texture_type_(
		_cube_texture_type
	),
	cube_sides_(
		_cube_sides
	)
{
}

sge::opengl::texture::type
sge::opengl::texture::cube_config::cube_texture_type() const
{
	return
		cube_texture_type_;
}

sge::opengl::texture::cube_side_array const &
sge::opengl::texture::cube_config::cube_sides() const
{
	return
		cube_sides_;
}
