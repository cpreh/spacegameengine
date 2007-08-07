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

sge::openal::player::player()
{
	// FIXME!
	alutInit(0, 0); check("alutInit");
}

void sge::openal::player::update()
{
	for (stream_sound_container_type::iterator i = stream_sounds.begin(); i != stream_sounds.end(); ++i)
		(*i)->update();
}

sge::shared_ptr<sge::sound> sge::openal::player::create_nonstream_sound(sge::shared_ptr<sge::audio_file> _audio_file)
{
	return shared_ptr<sound>(new nonstream_sound(_audio_file,*this));
}

sge::shared_ptr<sge::sound> sge::openal::player::create_stream_sound(sge::shared_ptr<sge::audio_file> _audio_file)
{
	return shared_ptr<sound>(new stream_sound(_audio_file,*this));
}

void sge::openal::player::check(const std::string &_desc)
{
	ALint error;
	if ((error = alGetError()) != AL_NO_ERROR)
		throw sge::audio_exception("OpenAL error ("+_desc+"): "+boost::lexical_cast<std::string>(error));
}

void sge::openal::player::listener_pos(const sge::math::vector3 &n)
{
	listener_pos_ = n;

	float vec[3] = { n.x(),n.y(),n.z() };
	alListenerfv(AL_POSITION, vec);
}

void sge::openal::player::listener_angle(const sge::sound_angle &n)
{
	listener_angle_ = n;

	float vec[6] = { n.forward.x(),n.forward.y(),n.forward.z(),n.up.x(),n.up.y(),n.up.z() };
	alListenerfv(AL_POSITION, vec);
}

ALuint sge::openal::player::register_nonstream_sound(sge::shared_ptr<sge::audio_file> af)
{
 	for (buffer_map_container_type::iterator i = buffer_map_.begin(); i != buffer_map_.end(); ++i)
	{
		if (i->file == &(*af))
		{
			(i->refcount)++;
			return i->buffer;
		}
	}

	buffer_map n;
	n.file = &(*af);

	// Buffer erstellen
	alGenBuffers(1, &n.buffer); check("alGenBuffers");

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
	alBufferData(n.buffer,format,&data[0],data.size(),_audio_file->sample_rate()); check("alGetError");

	n.refcount = 1;

	buffer_map_.push_back(n);
	return n.buffer;
}

void sge::openal::player::unregister_nonstream_sound(ALuint buffer)
{
 	for (buffer_map_container_type::iterator i = buffer_map_.begin(); i != buffer_map_.end(); ++i)
	{
		if (i->buffer == buffer)
		{
			if (--(i->refcount) == 0)
			{
				alDeleteBuffers(1,&(i->buffer));
				buffer_map_.erase(i);
				break;
			}
		}
	}
}
