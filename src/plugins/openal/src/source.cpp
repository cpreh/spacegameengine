#include "../source.hpp"
#include "../error.hpp"
#include <sge/audio/exception.hpp>

sge::openal::source::source()
	: status_(audio::sound_status::stopped),positional_(false)
{
	alGenSources(static_cast<ALsizei>(1),&source_); SGE_OPENAL_ERROR_CHECK;
}

sge::openal::source::source(ALuint const buffer)
	: status_(audio::sound_status::stopped),positional_(false)
{
	alGenSources(static_cast<ALsizei>(1),&source_); SGE_OPENAL_ERROR_CHECK;
	alSourcei(alsource(),AL_BUFFER,buffer); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::source::sync() const
{
	ALint play;
	alGetSourcei(alsource(), AL_SOURCE_STATE, &play); SGE_OPENAL_ERROR_CHECK;
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
			throw audio::exception(SGE_TEXT("OpenAL error: invalid playing status"));
		break;
	}
}

void sge::openal::source::play(audio::play_mode::type const _play_mode)
{
	sync();

	play_mode_ = _play_mode;
	alSourcei(alsource(),AL_LOOPING,play_mode_ == audio::play_mode::loop ? AL_TRUE : AL_FALSE); SGE_OPENAL_ERROR_CHECK

	if (status_ == audio::sound_status::playing)
		return;

	do_play();

	alSourcePlay(alsource()); SGE_OPENAL_ERROR_CHECK;
	status_ = audio::sound_status::playing;
}

void sge::openal::source::toggle_pause()
{
	sync();

	switch (status_)
	{
		case audio::sound_status::stopped:
			return;
		case audio::sound_status::paused:
			alSourcei(alsource(),AL_LOOPING,
				play_mode_ == audio::play_mode::loop ? AL_TRUE : AL_FALSE); SGE_OPENAL_ERROR_CHECK;
			alSourcePlay(alsource()); SGE_OPENAL_ERROR_CHECK;
		break;
		case audio::sound_status::playing:
			alSourcePause(alsource()); SGE_OPENAL_ERROR_CHECK;
		break;
	}
}

sge::audio::sound_status::type sge::openal::source::status() const
{
	sync();
	return status_;
}

void sge::openal::source::stop()
{
	sync();

	if (status_ == audio::sound_status::stopped)
		return;

	alSourceStop(alsource()); SGE_OPENAL_ERROR_CHECK;
	status_ = audio::sound_status::stopped;
}

void sge::openal::source::pos(audio::sound_pos const &n)
{
	pos_ = n;

	float const vec[3] = 
		{ 
			static_cast<float>(n.x()),
			static_cast<float>(n.y()),
			static_cast<float>(n.z()) 
		};

	alSourcefv(alsource(),AL_POSITION,vec); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::source::positional(bool const n)
{
	positional_ = n;

	if (n)
	{
		alSourcef(alsource(),AL_ROLLOFF_FACTOR,static_cast<float>(0.0)); SGE_OPENAL_ERROR_CHECK;
		alSourcei(alsource(),AL_SOURCE_RELATIVE, AL_TRUE); SGE_OPENAL_ERROR_CHECK;
	}
	else
	{
		alSourcef(alsource(),AL_ROLLOFF_FACTOR,static_cast<float>(1.0)); SGE_OPENAL_ERROR_CHECK;
		alSourcei(alsource(),AL_SOURCE_RELATIVE, AL_FALSE); SGE_OPENAL_ERROR_CHECK;
	}
}

sge::openal::source::~source()
{
	alDeleteSources(static_cast<ALsizei>(1),&source_); SGE_OPENAL_ERROR_CHECK;
}
