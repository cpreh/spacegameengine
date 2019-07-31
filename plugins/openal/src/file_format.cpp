//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/channel_type.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/file_format.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>


ALenum
sge::openal::file_format(
	sge::audio::file const &_file
)
{
	switch(
		_file.bits_per_sample().get()
	)
	{
	case 8u:
		switch(
			_file.channels().get()
		)
		{
		case 1u:
			return
				AL_FORMAT_MONO8;
		case 2u:
			return
				AL_FORMAT_STEREO8;
		}
		break;
	case 16u:
		switch(
			_file.channels().get()
		)
		{
		case 1u:
			return
				AL_FORMAT_MONO16;
		case 2u:
			return
				AL_FORMAT_STEREO16;
		}
		break;
	}

	throw
		sge::audio::exception(
			FCPPT_TEXT("OpenAL error: Format not supported: ")
			+
			fcppt::output_to_fcppt_string(
				_file.bits_per_sample()
			)
			+
			FCPPT_TEXT(" bps, ")
			+
			fcppt::output_to_fcppt_string(
				_file.channels()
			)
			+
			FCPPT_TEXT(" channels")
		);
}
