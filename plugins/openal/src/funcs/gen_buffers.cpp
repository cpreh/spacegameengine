//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/exception.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/funcs/gen_buffers.hpp>
#include <fcppt/text.hpp>


void
sge::openal::funcs::gen_buffers(
	ALuint *const _result,
	ALsizei const _count
)
{
	::alGenBuffers(
		_count,
		_result
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGenBuffers failed"),
		sge::audio::exception
	)
}
