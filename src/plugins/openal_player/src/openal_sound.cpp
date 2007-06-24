#include <string>
#include <boost/lexical_cast.hpp>
#include <AL/al.h>
#include <AL/alut.h>
#include "../../../audio/audio_player/sound.hpp"
#include "../../../audio/audio_exception.hpp"
#include "../openal_player.hpp"
#include "../openal_nonstream_sound.hpp"
#include "../openal_stream_sound.hpp"

sge::openal_player::openal_player() 
{
	alutInit(0, 0); check("alutInit");
}

void sge::openal_player::update()
{
	for (std::list<sound *>::iterator i = sounds.begin(); i != sounds.end(); ++i)
		(*i)->update();
}

sge::shared_ptr<sge::sound> sge::openal_player::create_nonstream_sound(sge::shared_ptr<sge::audio_file> _audio_file)
{
	return sge::shared_ptr<sge::sound>(new sge::openal_nonstream_sound(_audio_file,*this));
}

sge::shared_ptr<sge::sound> sge::openal_player::create_stream_sound(sge::shared_ptr<sge::audio_file> _audio_file)
{
	return sge::shared_ptr<sge::sound>(new sge::openal_stream_sound(_audio_file,*this));
}

void sge::openal_stream_sound::check(const std::string &_desc)
{
	ALint error;
	if ((error = alGetError()) != AL_NO_ERROR)
		throw sge::audio_exception("OpenAL error ("+_desc+"): "+boost::lexical_cast<std::string>(error));
}

void sge::openal_player::check(const std::string &_desc)
{
	ALint error;
	if ((error = alGetError()) != AL_NO_ERROR)
		throw sge::audio_exception("OpenAL error ("+_desc+"): "+boost::lexical_cast<std::string>(error));
}

void sge::openal_nonstream_sound::check(const std::string &_desc)
{
	ALint error;
	if ((error = alGetError()) != AL_NO_ERROR)
		throw sge::audio_exception("OpenAL error ("+_desc+"): "+boost::lexical_cast<std::string>(error));
}

sge::openal_nonstream_sound::openal_nonstream_sound(sge::shared_ptr<sge::audio_file> _audio_file,sge::openal_player &_player) : player_(_player)
{
	_player.register_sound(this);
	alGenBuffers(1, &al_buffer_); check("alGenBuffers");

	// Buffer erstellen
	ALenum format;
	if (_audio_file->bits_per_sample() == 8 && _audio_file->channels() == 1)
		format = AL_FORMAT_MONO8;
	else if (_audio_file->bits_per_sample() == 8 && _audio_file->channels() == 2)
		format = AL_FORMAT_STEREO8;
	else if (_audio_file->bits_per_sample() == 16 && _audio_file->channels() == 1)
		format = AL_FORMAT_MONO16;
	else if (_audio_file->bits_per_sample() == 16 && _audio_file->channels() == 2)
		format = AL_FORMAT_STEREO16;
	else 
		throw sge::audio_exception("OpenAL error: Format not supported: "+boost::lexical_cast<std::string>(_audio_file->bits_per_sample())+" bps, "+boost::lexical_cast<std::string>(_audio_file->channels())+" channels");

	std::vector<unsigned char> data;
	_audio_file->read_all(data);
	alBufferData(al_buffer_,format,&data[0],data.size(),_audio_file->sample_rate()); check("alGetError");

	// Source erstellen
	alGenSources(1,&al_source_); check("alGenSources");
	alSourcei(al_source_, AL_BUFFER, al_buffer_); check("alSourcei");

	alSource3f(al_source_,AL_POSITION,0.0,0.0,0.0);
	alSource3f(al_source_,AL_VELOCITY,0.0,0.0,0.0);
	alSource3f(al_source_,AL_DIRECTION,0.0,0.0,0.0);
	alSourcef(al_source_,AL_ROLLOFF_FACTOR,0.0);
	alSourcei(al_source_,AL_SOURCE_RELATIVE, AL_TRUE);

	status_ = status_loaded;
}

void sge::openal_nonstream_sound::play(const bool _loop)
{
	loop_ = _loop;
	alSourcei(al_source_,AL_LOOPING,loop_ ? AL_TRUE : AL_FALSE);
	if (status_ == status_playing)
		return;

	alSourcePlay(al_source_);
	status_ = status_playing;
}

void sge::openal_nonstream_sound::stop()
{
	// Wenn nicht gestoppt werden muss
	if (status_ == status_stopped)
		return;
	
	alSourceStop(al_source_);
	status_ = status_stopped;
}

// Achtung! toggle_pause schaltet nur von playing auf paused und von paused auf playing um, nichts anderes!
void sge::openal_nonstream_sound::toggle_pause()
{
	if (status_ == status_stopped || status_ == status_loaded)
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

sge::openal_nonstream_sound::~openal_nonstream_sound()
{
	player_.unregister_sound(this);
}

sge::openal_stream_sound::openal_stream_sound(sge::shared_ptr<sge::audio_file> _audio_file,sge::openal_player &_player) 
	: player_(_player),audio_file_(_audio_file)
{
	_player.register_sound(this);
	alGenBuffers(2, al_buffers_); check("alGenBuffers");

	// Buffer erstellen
	if (_audio_file->bits_per_sample() == 8 && _audio_file->channels() == 1)
		format_ = AL_FORMAT_MONO8;
	else if (_audio_file->bits_per_sample() == 8 && _audio_file->channels() == 2)
		format_ = AL_FORMAT_STEREO8;
	else if (_audio_file->bits_per_sample() == 16 && _audio_file->channels() == 1)
		format_ = AL_FORMAT_MONO16;
	else if (_audio_file->bits_per_sample() == 16 && _audio_file->channels() == 2)
		format_ = AL_FORMAT_STEREO16;
	else 
		throw sge::audio_exception("OpenAL error: Format not supported: "+boost::lexical_cast<std::string>(_audio_file->bits_per_sample())+" bps, "+boost::lexical_cast<std::string>(_audio_file->channels())+" channels");

	// Immer 2 Sekunden im Cache haben
	buffer_samples_ = 2*_audio_file->sample_rate();
	
	// Source erstellen
	alGenSources(1,&al_source_); check("alGenSources");

	alSource3f(al_source_,AL_POSITION,0.0,0.0,0.0);
	alSource3f(al_source_,AL_VELOCITY,0.0,0.0,0.0);
	alSource3f(al_source_,AL_DIRECTION,0.0,0.0,0.0);
	alSourcef(al_source_,AL_ROLLOFF_FACTOR,0.0);
	alSourcei(al_source_,AL_SOURCE_RELATIVE, AL_TRUE);

	status_ = status_loaded;
}

sge::openal_stream_sound::~openal_stream_sound()
{
	player_.unregister_sound(this);
}

bool sge::openal_stream_sound::fill_buffer(ALuint buffer)
{
	std::vector<unsigned char> data;
	std::size_t samples_read = audio_file_->read(buffer_samples_,data);

	if (samples_read == 0)
	{
		// Nichts mehr nachzuladen, aber es soll geloopt werden? Dann resetten und von vorne nachladen
		if (loop_)
		{
			audio_file_->reset();
			samples_read = audio_file_->read(buffer_samples_,data);
		}
		else
		{
			return false;
		}
	}
	alBufferData(buffer,format_,&data[0],data.size(),audio_file_->sample_rate()); check("alBufferData");
	return true;
}

void sge::openal_stream_sound::play(const bool _loop)
{
	loop_ = _loop;
	alSourcei(al_source_,AL_LOOPING,_loop ? AL_TRUE : AL_FALSE);
	if (status_ == status_playing)
		return;

	// Datei resetten und Puffer fuellen
	audio_file_->reset();
	fill_buffer(al_buffers_[0]);
	fill_buffer(al_buffers_[1]);

	alSourceQueueBuffers(al_source_,2,al_buffers_); check("alSourceQueueBuffers");
	alSourcePlay(al_source_); check("alSourcePlay");

	status_ = status_playing;
}

void sge::openal_stream_sound::toggle_pause()
{
	if (status_ == status_stopped || status_ == status_loaded)
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

void sge::openal_nonstream_sound::update()
{
	ALint play;
	alGetSourcei(al_source_, AL_SOURCE_STATE, &play);
	if (play == AL_STOPPED)
		status_ = status_stopped;
}

void sge::openal_stream_sound::stop()
{
	// Wenn nicht gestoppt werden muss
	if (status_ == status_stopped)
		return;
	
	alSourceStop(al_source_);
	status_ = status_stopped;
}

void sge::openal_stream_sound::update()
{
	ALint play;
	alGetSourcei(al_source_, AL_SOURCE_STATE, &play);
	if (play == AL_STOPPED)
		status_ = status_stopped;

	ALint processed;
	alGetSourcei(al_source_, AL_BUFFERS_PROCESSED, &processed);

	while(processed--)
	{
		ALuint buffer;
		// Unqueuen bewirkt, dass der Puffer von oben weggenommen wird...
		alSourceUnqueueBuffers(al_source_, 1, &buffer); check("alSourceUnqueueBuffers");
		// ...und Queue bewirkt, dass es hinten angefuegt wird. Genial!
		if (fill_buffer(buffer))
			alSourceQueueBuffers(al_source_, 1, &buffer); check("alSourceQueueBuffers");
	}
}
