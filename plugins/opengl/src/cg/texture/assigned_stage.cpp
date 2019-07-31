//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/check_state.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/cg/texture/assigned_stage.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::texture::stage
sge::opengl::cg::texture::assigned_stage(
	sge::cg::parameter::object const &_parameter
)
{
	GLenum const ret(
		::cgGLGetTextureEnum(
			_parameter.get()
		)
	);

	if(
		ret
		==
		GL_INVALID_OPERATION
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("cgGLGetTextureEnum failed")
		);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGLGetTextureEnum failed"),
		sge::renderer::exception
	)

	FCPPT_ASSERT_ERROR(
		ret >= GL_TEXTURE0_ARB
	);

	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::texture::stage,
			fcppt::cast::static_cast_fun
		>(
			ret
			-
			GL_TEXTURE0_ARB
		);
}
