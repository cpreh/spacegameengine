//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/exception.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/funcs/buffer_data.hpp>
#include <fcppt/text.hpp>


void
sge::openal::funcs::buffer_data(
	sge::openal::buffer_id const _buffer,
	ALenum const _format,
	ALvoid const *const _data,
	ALsizei const _size,
	ALsizei const _freq
)
{
	::alBufferData(
		_buffer.get(),
		_format,
		_data,
		_size,
		_freq
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alBufferData failed"),
		sge::audio::exception
	)
}
