//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/check_state.hpp>
#include <sge/opengl/cg/profile/get_latest.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


CGprofile
sge::opengl::cg::profile::get_latest(
	CGGLenum const _type
)
{
	CGprofile const ret(
		::cgGLGetLatestProfile(
			_type
		)
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGLGetLatestProfile failed!"),
		sge::renderer::exception
	)

	FCPPT_ASSERT_THROW(
		ret
		!=
		CG_PROFILE_UNKNOWN,
		sge::renderer::exception
	);

	return ret;
}
