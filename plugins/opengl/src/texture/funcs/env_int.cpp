//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/active_level_fwd.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>
#include <sge/opengl/texture/funcs/env_target.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::texture::funcs::env_int(
	sge::opengl::texture::active_level const &,
	sge::opengl::texture::funcs::env_target const _target,
	sge::opengl::texture::funcs::env_arg const _arg,
	sge::opengl::texture::funcs::env_int_value const _value
)
{
	sge::opengl::call(
		::glTexEnvi,
		_target.get(),
		_arg.get(),
		_value.get()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glTexEnvi failed"),
		sge::renderer::exception
	)
}
