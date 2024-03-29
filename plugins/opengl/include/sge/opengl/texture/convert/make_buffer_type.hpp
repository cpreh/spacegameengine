//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_CONVERT_MAKE_BUFFER_TYPE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CONVERT_MAKE_BUFFER_TYPE_HPP_INCLUDED

#include <sge/opengl/texture/buffer_type.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>

namespace sge::opengl::texture::convert
{

template <int Type>
inline constexpr sge::opengl::texture::buffer_type make_buffer_type{
    fcppt::strong_typedef_construct_cast<
        sge::opengl::texture::buffer_type,
        fcppt::cast::static_cast_fun>(Type)};
}

#endif
