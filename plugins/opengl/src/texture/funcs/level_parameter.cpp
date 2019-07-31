//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/funcs/level_parameter.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>


GLint
sge::opengl::texture::funcs::level_parameter(
	sge::opengl::texture::binding const &,
	sge::opengl::texture::buffer_type const _type,
	sge::renderer::texture::mipmap::level const _level,
	GLenum const _what
)
{
	GLint ret;

	sge::opengl::call(
		::glGetTexLevelParameteriv,
		_type.get(),
		fcppt::cast::to_signed(
			_level.get()
		),
		_what,
		&ret
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetTexLevelParameteriv() failed!"),
		sge::renderer::exception
	)

	return
		ret;
}
