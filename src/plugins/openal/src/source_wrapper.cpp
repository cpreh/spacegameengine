#include "../source_wrapper.hpp"
#include "../error.hpp"
#include <sge/audio/exception.hpp>

sge::openal::source_wrapper::source_wrapper()
	: status_(sound_status::stopped)
{
	alGenSources(static_cast<ALsizei>(1),&source_);
	SGE_OPENAL_ERROR_CHECK
}

void sge::openal::source_wrapper::sync()
{
	ALint play;
	alGetSourcei(source_, AL_SOURCE_STATE, &play);
	SGE_OPENAL_ERROR_CHECK
	switch (play)
	{
		case AL_STOPPED:
			status_ = sound_status::stopped;
		break;
		case AL_PAUSED:
			status_ = sound_status::paused;
		break;
		case AL_PLAYING:
			status_ = sound_status::playing;
		break;
		default:
			throw audio::exception("OpenAL error: invalid playing status");
		break;
	}
}

sge::openal::source_wrapper::~source_wrapper()
{
	alDeleteSources(static_cast<ALsizei>(1),&source_);
	SGE_OPENAL_ERROR_CHECK
}
