/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../nonstream_sound.hpp"
#include "../player.hpp"
#include "../error.hpp"

sge::openal::nonstream_sound::nonstream_sound(
	const audio::file_ptr _audio_file,
	openal::player &_player)
: source(_player.register_nonstream_sound(_audio_file)),
  player_(_player)
{
}

void sge::openal::nonstream_sound::play_mode(sge::audio::play_mode::type pm)
{
	source::play_mode(pm);
	
	alSourcei(
		alsource(),
		AL_LOOPING,
		source::play_mode() == audio::play_mode::loop 
			? AL_TRUE 
			: AL_FALSE); SGE_OPENAL_ERROR_CHECK
}

sge::openal::nonstream_sound::~nonstream_sound()
{
	player_.unregister_nonstream_sound(albuffer());
}
