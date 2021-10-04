//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CONFIG_FWD_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CONFIG_FWD_HPP_INCLUDED

#include <sge/opengl/texture/config_impl.hpp>
#include <fcppt/math/size_type.hpp>


namespace sge::opengl::texture
{

template<
	fcppt::math::size_type Size
>
using
config
=
typename
sge::opengl::texture::config_impl<
	Size
>::type;

}

#endif
