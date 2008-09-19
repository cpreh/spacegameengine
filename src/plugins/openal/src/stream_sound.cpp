/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../player.hpp"
#include "../nonstream_sound.hpp"
#include "../stream_sound.hpp"
#include "../openal.hpp"
#include "../error.hpp"
#include "../file_format.hpp"
#include <sge/audio/player/sound.hpp>
#include <sge/audio/exception.hpp>
#include <sge/raw_vector_impl.hpp>
#include <boost/lexical_cast.hpp>

sge::openal::stream_sound::stream_sound(audio::file_ptr const _audio_file, player &_player)
	: player_(_player),
	  audio_file_(_audio_file),
		buffer_samples_(static_cast<audio::sample_type>(2*_audio_file->sample_rate())),
		format_(file_format(*_audio_file))
{
	_player.register_stream_sound(this);

	alGenBuffers(static_cast<ALsizei>(2), al_buffers_); SGE_OPENAL_ERROR_CHECK;
}

sge::openal::stream_sound::~stream_sound()
{
	player_.unregister_stream_sound(this);
}

bool sge::openal::stream_sound::fill_buffer(ALuint const buffer)
{
	audio::raw_array_type data;
	audio::sample_type samples_read = 
		audio_file_->read(buffer_samples_, data);

	if (samples_read == static_cast<audio::sample_type>(0))
	{
		// Nichts mehr nachzuladen, aber es soll geloopt werden? Dann resetten und von vorne nachladen
		if (play_mode() != audio::play_mode::loop)
			return false;

		audio_file_->reset();
		samples_read = audio_file_->read(buffer_samples_,data);
	}

	alBufferData(
		buffer, 
		format_, 
		data.data(), 
		static_cast<ALsizei>(data.size()), 
		static_cast<ALsizei>(audio_file_->sample_rate())); SGE_OPENAL_ERROR_CHECK;

	return true;
}

void sge::openal::stream_sound::do_play()
{
	// reset file and fill buffers
	audio_file_->reset();
	fill_buffer(al_buffers_[0]);
	fill_buffer(al_buffers_[1]);

	alSourceQueueBuffers(source(),static_cast<ALsizei>(2),al_buffers_); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::stream_sound::update()
{
	sync();

	ALint processed;
	alGetSourcei(source(), AL_BUFFERS_PROCESSED, &processed);

	while(processed--)
	{
		ALuint buffer;
		// Unqueuen bewirkt, dass der Puffer von oben weggenommen wird...
		alSourceUnqueueBuffers(source(),static_cast<ALsizei>(1),&buffer);
		// ...und Queue bewirkt, dass es hinten angefuegt wird. Genial!
		if (fill_buffer(buffer))
			alSourceQueueBuffers(source(),static_cast<ALsizei>(1),&buffer);
	}
}
