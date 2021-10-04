//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CONFIG_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CONFIG_IMPL_HPP_INCLUDED

#include <sge/opengl/texture/surface_config_fwd.hpp>
#include <sge/opengl/texture/volume_config_fwd.hpp>
#include <fcppt/math/size_type.hpp>


namespace sge::opengl::texture
{

template<
	fcppt::math::size_type Size
>
struct config_impl;

template<>
struct config_impl<
	2U
>
{
	using
	type
	=
	sge::opengl::texture::surface_config;
};

template<>
struct config_impl<
	3U
>
{
	using
	type
	=
	sge::opengl::texture::volume_config;
};

}

#endif
