/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_AUDIO_NULL_PLAYER_HPP_INCLUDED
#define SGE_AUDIO_NULL_PLAYER_HPP_INCLUDED

#include "listener.hpp"
#include <sge/audio/player.hpp>

namespace sge
{
namespace audio_null
{

class player : public audio::player {
public:
	explicit
	player();

	audio::listener &
	listener();

	audio::scalar 
	speed_of_sound() const { return audio::scalar(); }

	void 
	speed_of_sound(
		audio::scalar) {}

	audio::scalar
	gain() const { return audio::scalar(); }

	void
	gain(
		audio::scalar) {}

	audio::buffer_ptr const
	create_buffer(
		audio::file_ptr);

	audio::sound::positional_ptr const 
	create_positional_stream(
		audio::file_ptr,
		audio::sound::positional_parameters const &);

	audio::sound::base_ptr const 
	create_nonpositional_stream(
		audio::file_ptr);
	
	audio::player_capabilities_field const
	capabilities() const;
private:
	audio_null::listener listener_;
};

}
}

#endif
