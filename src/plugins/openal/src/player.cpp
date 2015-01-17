/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/direction/forward.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/audio/direction/up.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/buffer.hpp>
#include <sge/openal/file_format.hpp>
#include <sge/openal/player.hpp>
#include <sge/openal/stream_sound.hpp>
#include <sge/openal/funcs/doppler_factor.hpp>
#include <sge/openal/funcs/listener_float.hpp>
#include <sge/openal/funcs/speed_of_sound.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::openal::player::player()
:
	device_(),
	context_(
		device_
	),
	current_context_(
		context_
	),
	listener_()
{
	// set our own speed of sound standard rather than relying on OpenAL
	this->speed_of_sound(
		343.f
	);

	this->listener().position(
		sge::audio::vector::null()
	);

	this->listener().linear_velocity(
		sge::audio::vector::null()
	);

	this->listener().direction(
		sge::audio::direction::object(
			sge::audio::direction::forward(
				sge::audio::vector(
					0.f,
					0.f,
					1.f
				)
			),
			sge::audio::direction::up(
				sge::audio::vector(
					0.f,
					1.f,
					0.f
				)
			)
		)
	);
}

sge::openal::player::~player()
{
}

sge::audio::listener &
sge::openal::player::listener()
{
	return listener_;
}

void
sge::openal::player::speed_of_sound(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::speed_of_sound(
		static_cast<
			ALfloat
		>(
			_value
		)
	);
}

void
sge::openal::player::doppler_factor(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::doppler_factor(
		static_cast<
			ALfloat
		>(
			_value
		)
	);
}

void
sge::openal::player::gain(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::listener_float(
		AL_GAIN,
		static_cast<
			ALfloat
		>(
			_value
		)
	);
}

sge::audio::buffer_unique_ptr
sge::openal::player::create_buffer(
	sge::audio::file &_file
)
{
	return
		fcppt::make_unique_ptr<
			sge::openal::buffer
		>(
			_file
		);
}

sge::audio::sound::positional_unique_ptr
sge::openal::player::create_positional_stream(
	sge::audio::file &_file,
	sge::audio::sound::positional_parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sge::openal::stream_sound
		>(
			_parameters,
			_file
		);
}

sge::audio::sound::base_unique_ptr
sge::openal::player::create_nonpositional_stream(
	sge::audio::file &_file,
	sge::audio::sound::nonpositional_parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sge::openal::stream_sound
		>(
			_parameters,
			_file
		);
}

bool
sge::openal::player::is_null() const
{
	return
		false;
}
