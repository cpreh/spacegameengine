//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/exception.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/get_source_int.hpp>
#include <fcppt/text.hpp>


ALint
sge::openal::funcs::get_source_int(
	sge::openal::source_id const _source,
	ALenum const _what
)
{
	ALint result{};

	::alGetSourcei(
		_source.get(),
		_what,
		&result
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGetSourcei failed"),
		sge::audio::exception
	)

	return
		result;
}
