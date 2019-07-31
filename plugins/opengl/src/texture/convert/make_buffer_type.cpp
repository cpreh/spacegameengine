//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/convert/make_buffer_type.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>


sge::opengl::texture::buffer_type
sge::opengl::texture::convert::make_buffer_type(
	int const _type
)
{
	// TODO: Template
	return
		fcppt::strong_typedef_construct_cast<
			sge::opengl::texture::buffer_type,
			fcppt::cast::static_cast_fun
		>(
			_type
		);
}
