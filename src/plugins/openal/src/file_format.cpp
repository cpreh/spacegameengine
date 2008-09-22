#include "../file_format.hpp"
#include <sge/audio/file.hpp>
#include <sge/audio/exception.hpp>
#include <sge/text.hpp>
#include <sge/iostream.hpp>
#include <boost/lexical_cast.hpp>

ALenum sge::openal::file_format(audio::file const &file)
{
	if (file.bits_per_sample() == static_cast<audio::sample_count>(8) && file.channels() == static_cast<audio::channel_type>(1))
		return AL_FORMAT_MONO8;
	if (file.bits_per_sample() == static_cast<audio::sample_count>(8) && file.channels() == static_cast<audio::channel_type>(2))
		return AL_FORMAT_STEREO8;
	if (file.bits_per_sample() == static_cast<audio::sample_count>(16) && file.channels() == static_cast<audio::channel_type>(1))
		return AL_FORMAT_MONO16;
	if (file.bits_per_sample() == static_cast<audio::sample_count>(16) && file.channels() == static_cast<audio::channel_type>(2))
		return AL_FORMAT_STEREO16;
	
	throw audio::exception(SGE_TEXT("OpenAL error: Format not supported: ")
												+ boost::lexical_cast<string>(file.bits_per_sample())
												+ SGE_TEXT(" bps, ")
												+ boost::lexical_cast<string>(file.channels())
												+ SGE_TEXT(" channels"));

	return AL_FORMAT_MONO8;
}
