/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/audio_null/listener.hpp>
#include <sge/audio/buffer_ptr.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/file_ptr.hpp>
#include <sge/audio/listener_fwd.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/player_capabilities_field.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio_null
{

class player
:
	public audio::player
{
	FCPPT_NONCOPYABLE(
		player
	);
public:
	player();

	~player();

	audio::listener &
	listener();

	audio::scalar
	speed_of_sound() const;

	audio::scalar
	doppler_factor() const;

	void
	speed_of_sound(
		audio::scalar
	);

	void
	doppler_factor(
		audio::scalar
	);

	audio::scalar
	gain() const;

	void
	gain(
		audio::scalar
	);

	audio::buffer_ptr const
	create_buffer(
		audio::file &
	);

	audio::sound::positional_ptr const
	create_positional_stream(
		audio::file_ptr,
		audio::sound::positional_parameters const &
	);

	audio::sound::base_ptr const
	create_nonpositional_stream(
		audio::file_ptr,
		audio::sound::nonpositional_parameters const &
	);

	audio::player_capabilities_field const
	capabilities() const;
private:
	audio_null::listener listener_;
};

}
}

#endif
