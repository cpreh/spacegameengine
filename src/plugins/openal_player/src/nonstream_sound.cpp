#include <string>
#include <boost/lexical_cast.hpp>
// FIXME: No AL/ in OpenAL SDK for Windows.
#include <AL/al.h>
#include <AL/alut.h>
#include "../../../audio/audio_player/sound.hpp"
#include "../../../audio/audio_exception.hpp"
#include "../openal_player.hpp"
#include "../openal_nonstream_sound.hpp"
#include "../openal_stream_sound.hpp"

void sge::openal::nonstream_sound::check(const std::string &_desc)
{
	ALint error;
	if ((error = alGetError()) != AL_NO_ERROR)
		throw sge::audio_exception("OpenAL error ("+_desc+"): "+boost::lexical_cast<std::string>(error));
}

sge::openal::nonstream_sound::nonstream_sound(sge::shared_ptr<sge::audio_file> _audio_file,sge::openal::player &_player) : player_(_player)
{
	al_buffer_ = _player.register_nonstream_sound(_audio_file);

	// Source erstellen
	alGenSources(1,&al_source_); check("alGenSources");
	alSourcei(al_source_, AL_BUFFER, al_buffer_); check("alSourcei");

	status_ = status_stopped;
}

void sge::openal::nonstream_sound::play(const bool _loop)
{
	sync();
	
	loop_ = _loop;
	alSourcei(al_source_,AL_LOOPING,loop_ ? AL_TRUE : AL_FALSE);
	if (status_ == status_playing)
		return;

	alSourcePlay(al_source_);
	status_ = status_playing;
}

void sge::openal::nonstream_sound::stop()
{
	sync();

	// Wenn nicht gestoppt werden muss
	if (status_ == status_stopped)
		return;

	alSourceStop(al_source_);
	status_ = status_stopped;
}

// Achtung! toggle_pause schaltet nur von playing auf paused und von paused auf playing um, nichts anderes!
void sge::openal::nonstream_sound::toggle_pause()
{
	sync();

	if (status_ == status_stopped)
		return;

	if (status_ == status_paused)
	{
		alSourcei(al_source_,AL_LOOPING,loop_ ? AL_TRUE : AL_FALSE);
		alSourcePlay(al_source_);
	}
	else
	{
		alSourcePause(al_source_);
	}
}

sge::openal::nonstream_sound::~nonstream_sound()
{
	player_.unregister_nonstream_sound(al_buffer_);
}

void sge::openal::nonstream_sound::sync()
{
	ALint play;
	alGetSourcei(al_source_, AL_SOURCE_STATE, &play);
	if (play == AL_STOPPED)
		status_ = status_stopped;
	else if (play == AL_PAUSED)
		status_ = status_paused;
	else if (play == AL_PLAYING)
		status_ = status_playing;
}

void sge::openal::nonstream_sound::positional(const bool n)
{
	positional_ = n;

	if (!n)
	{
		alSourcef(al_source_,AL_ROLLOFF_FACTOR,0.0);
		alSourcei(al_source_,AL_SOURCE_RELATIVE, AL_TRUE);
	}
	else
	{
		alSourcef(al_source_,AL_ROLLOFF_FACTOR,1.0);
		alSourcei(al_source_,AL_SOURCE_RELATIVE, AL_FALSE);
	}
}

void sge::openal::nonstream_sound::pos(const sge::math::vector3 &n)
{
	pos_ = n;

	float vec[3] = { n.x(),n.y(),n.z() };
	alSourcefv(al_source_,AL_POSITION,vec);
}
