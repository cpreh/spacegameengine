//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/bad_sound_alloc.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/gen_source.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>


sge::openal::source_id
sge::openal::funcs::gen_source()
{
	ALuint result{};

	::alGenSources(
		fcppt::literal<
			ALsizei
		>(
			1
		),
		&result
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGenSources failed"),
		sge::audio::bad_sound_alloc
	)

	return
		sge::openal::source_id(
			result
		);
}
