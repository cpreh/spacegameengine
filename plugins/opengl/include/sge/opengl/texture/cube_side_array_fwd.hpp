//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CUBE_SIDE_ARRAY_FWD_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_SIDE_ARRAY_FWD_HPP_INCLUDED

#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <fcppt/enum/array_fwd.hpp>


namespace sge::opengl::texture
{

using
cube_side_array
=
fcppt::enum_::array<
	sge::renderer::texture::cube_side,
	sge::opengl::texture::buffer_type
>;

}

#endif
