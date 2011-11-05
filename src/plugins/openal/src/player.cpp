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


#include <sge/openal/player.hpp>
#include <sge/openal/stream_sound.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/file_format.hpp>
#include <sge/openal/log.hpp>
#include <sge/openal/buffer.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sample_container.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/positional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/log/headers.hpp>


sge::openal::player::player()
:
	device_(),
	context_(
		device_),
	listener_()
{
	context_.make_current();

	// set our own speed of sound standard rather than relying on OpenAL
	this->speed_of_sound(
		static_cast<audio::scalar>(
			343));

	this->listener().position(
		audio::vector::null());
	this->listener().linear_velocity(
		audio::vector::null());
	this->listener().direction(
		audio::direction::object(
			audio::direction::forward(
				audio::vector(
					static_cast<audio::scalar>(0),
					static_cast<audio::scalar>(0),
					static_cast<audio::scalar>(1))),
			audio::direction::up(
				audio::vector(
					static_cast<audio::scalar>(0),
					static_cast<audio::scalar>(1),
					static_cast<audio::scalar>(0)))));
}

sge::openal::player::~player()
{}

sge::audio::listener &
sge::openal::player::listener()
{
	return listener_;
}

void
sge::openal::player::speed_of_sound(
	audio::scalar const dest)
{
	alSpeedOfSound(
		static_cast<ALfloat>(
			dest));
}

void
sge::openal::player::doppler_factor(
	audio::scalar const dest)
{
	alDopplerFactor(
		static_cast<ALfloat>(
			dest));
}

void
sge::openal::player::gain(
	audio::scalar const g)
{
	alListenerf(
		AL_GAIN,
		g);
}

sge::audio::buffer_ptr const
sge::openal::player::create_buffer(
	audio::file &_file
)
{
	return
		audio::buffer_ptr(
			fcppt::make_shared_ptr<
				openal::buffer
			>(
				fcppt::ref(
					_file
				)
			)
		);
}

sge::audio::sound::positional_ptr const
sge::openal::player::create_positional_stream(
	audio::file_ptr const _file,
	audio::sound::positional_parameters const &_parameters
)
{
	return
		audio::sound::positional_ptr(
			fcppt::make_shared_ptr<
				openal::stream_sound
			>(
				fcppt::cref(
					_parameters
				),
				_file
			)
		);
}

sge::audio::sound::base_ptr const
sge::openal::player::create_nonpositional_stream(
	audio::file_ptr const _file,
	audio::sound::nonpositional_parameters const &_parameters
)
{
	return
		audio::sound::positional_ptr(
			fcppt::make_shared_ptr<
				openal::stream_sound
			>(
				fcppt::cref(
					_parameters),
				_file
			)
		);
}


sge::audio::player_capabilities_field const
sge::openal::player::capabilities() const
{
	return audio::player_capabilities_field::null();
}
