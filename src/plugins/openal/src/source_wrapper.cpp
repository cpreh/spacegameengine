#include "../source_wrapper.hpp"
#include "../error.hpp"
#include <sge/audio/exception.hpp>

sge::openal::source_wrapper::source_wrapper()
	: status_(audio::sound_status::stopped)
{
	alGenSources(static_cast<ALsizei>(1),&source_); SGE_OPENAL_ERROR_CHECK;
}

sge::openal::source_wrapper::source_wrapper(ALuint const buffer)
	: status_(audio::sound_status::stopped)
{
	alGenSources(static_cast<ALsizei>(1),&source_); SGE_OPENAL_ERROR_CHECK;
	alSourcei(source(),AL_BUFFER,buffer); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::source_wrapper::sync() const
{
	ALint play;
	alGetSourcei(source(), AL_SOURCE_STATE, &play); SGE_OPENAL_ERROR_CHECK;
	switch (play)
	{
		case AL_STOPPED:
		case AL_INITIAL:
			status_ = audio::sound_status::stopped;
		break;
		case AL_PAUSED:
			status_ = audio::sound_status::paused;
		break;
		case AL_PLAYING:
			status_ = audio::sound_status::playing;
		break;
		default:
			throw audio::exception("OpenAL error: invalid playing status");
		break;
	}
}

void sge::openal::source_wrapper::play(audio::play_mode::type const _play_mode)
{
	sync();

	play_mode_ = _play_mode;
	alSourcei(source(),AL_LOOPING,play_mode_ == audio::play_mode::loop ? AL_TRUE : AL_FALSE); SGE_OPENAL_ERROR_CHECK

	if (status_ == audio::sound_status::playing)
		return;

	do_play();

	alSourcePlay(source()); SGE_OPENAL_ERROR_CHECK;
	status_ = audio::sound_status::playing;
}

void sge::openal::source_wrapper::toggle_pause()
{
	sync();

	switch (status_)
	{
		case audio::sound_status::stopped:
			return;
		case audio::sound_status::paused:
			alSourcei(source(),AL_LOOPING,
				play_mode_ == audio::play_mode::loop ? AL_TRUE : AL_FALSE); SGE_OPENAL_ERROR_CHECK;
			alSourcePlay(source()); SGE_OPENAL_ERROR_CHECK;
		break;
		case audio::sound_status::playing:
			alSourcePause(source()); SGE_OPENAL_ERROR_CHECK;
		break;
	}
}

sge::audio::sound_status::type sge::openal::source_wrapper::status() const
{
	sync();
	return status_;
}

void sge::openal::source_wrapper::stop()
{
	sync();

	if (status_ == audio::sound_status::stopped)
		return;

	alSourceStop(source()); SGE_OPENAL_ERROR_CHECK;
	status_ = audio::sound_status::stopped;
}

void sge::openal::source_wrapper::pos(math::vector3 const &n)
{
	pos_ = n;

	float const vec[3] = 
		{ 
			static_cast<float>(n.x()),
			static_cast<float>(n.y()),
			static_cast<float>(n.z()) 
		};

	alSourcefv(source(),AL_POSITION,vec); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::source_wrapper::positional(bool const n)
{
	positional_ = n;

	if (!n)
	{
		alSourcef(source(),AL_ROLLOFF_FACTOR,static_cast<float>(0.0)); SGE_OPENAL_ERROR_CHECK;
		alSourcei(source(),AL_SOURCE_RELATIVE, AL_TRUE); SGE_OPENAL_ERROR_CHECK;
	}
	else
	{
		alSourcef(source(),AL_ROLLOFF_FACTOR,static_cast<float>(1.0)); SGE_OPENAL_ERROR_CHECK;
		alSourcei(source(),AL_SOURCE_RELATIVE, AL_FALSE); SGE_OPENAL_ERROR_CHECK;
	}
}

sge::openal::source_wrapper::~source_wrapper()
{
	alDeleteSources(static_cast<ALsizei>(1),&source_); SGE_OPENAL_ERROR_CHECK;
}
