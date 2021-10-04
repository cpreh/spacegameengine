//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CUBE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_CONFIG_HPP_INCLUDED

#include <sge/opengl/texture/cube_config_fwd.hpp>
#include <sge/opengl/texture/cube_side_array.hpp>
#include <sge/opengl/texture/type.hpp>


namespace sge::opengl::texture
{

class cube_config
{
public:
	cube_config(
		sge::opengl::texture::type,
		sge::opengl::texture::cube_side_array const &
	);

	[[nodiscard]]
	sge::opengl::texture::type
	cube_texture_type() const;

	[[nodiscard]]
	sge::opengl::texture::cube_side_array const &
	cube_sides() const;
private:
	sge::opengl::texture::type cube_texture_type_;

	sge::opengl::texture::cube_side_array cube_sides_;
};

}

#endif
