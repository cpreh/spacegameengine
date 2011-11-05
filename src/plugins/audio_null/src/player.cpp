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


#include <sge/audio_null/player.hpp>
#include <sge/audio_null/positional.hpp>
#include <sge/audio_null/buffer.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>


sge::audio_null::player::player()
:
	listener_()
{
}

sge::audio_null::player::~player()
{
}

sge::audio::listener &
sge::audio_null::player::listener()
{
	return listener_;
}

sge::audio::scalar
sge::audio_null::player::speed_of_sound() const
{
	return audio::scalar();
}

sge::audio::scalar
sge::audio_null::player::doppler_factor() const
{
	return audio::scalar();
}

void
sge::audio_null::player::speed_of_sound(
	audio::scalar
)
{
}

void
sge::audio_null::player::doppler_factor(
	audio::scalar
)
{
}

sge::audio::scalar
sge::audio_null::player::gain() const
{
	return audio::scalar();
}

void
sge::audio_null::player::gain(
	audio::scalar
)
{
}

sge::audio::buffer_ptr const
sge::audio_null::player::create_buffer(
	audio::file &
)
{
	return
		sge::audio::buffer_ptr(
			fcppt::make_shared_ptr<
				audio_null::buffer
			>()
		);
}

sge::audio::sound::positional_ptr const
sge::audio_null::player::create_positional_stream(
	audio::file_ptr,
	audio::sound::positional_parameters const &
)
{
	return
		sge::audio::sound::positional_ptr(
			fcppt::make_shared_ptr<
				audio_null::positional
			>()
		);
}

sge::audio::sound::base_ptr const
sge::audio_null::player::create_nonpositional_stream(
	audio::file_ptr,
	audio::sound::nonpositional_parameters const &
)
{
	return
		sge::audio::sound::positional_ptr(
			fcppt::make_shared_ptr<
				audio_null::positional
			>()
		);
}

sge::audio::player_capabilities_field const
sge::audio_null::player::capabilities() const
{
	return
		sge::audio::player_capabilities_field(
			sge::audio::player_capabilities::null
		);
}
