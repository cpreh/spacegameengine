/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/audio/scalar.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/sound/optional_direction_fwd.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/audio_null/positional.hpp>


sge::audio_null::positional::positional()
{
}

sge::audio_null::positional::~positional()
{
}

void
sge::audio_null::positional::play(
	sge::audio::sound::repeat
)
{
}

void
sge::audio_null::positional::toggle_pause()
{
}

sge::audio::sound::play_status
sge::audio_null::positional::status() const
{
	return audio::sound::play_status::stopped;
}

void
sge::audio_null::positional::stop()
{
}

void
sge::audio_null::positional::update()
{
}

void
sge::audio_null::positional::position(
	sge::audio::vector const &
)
{
}

void
sge::audio_null::positional::linear_velocity(
	sge::audio::vector const &
)
{
}

void
sge::audio_null::positional::gain(
	sge::audio::scalar
)
{
}

void
sge::audio_null::positional::pitch(
	sge::audio::scalar
)
{
}

void
sge::audio_null::positional::rolloff_factor(
	sge::audio::scalar
)
{
}

void
sge::audio_null::positional::reference_distance(
	sge::audio::scalar
)
{
}

void
sge::audio_null::positional::max_distance(
	sge::audio::scalar
)
{
}

void
sge::audio_null::positional::direction(
	sge::audio::sound::optional_direction const &
)
{
}

void
sge::audio_null::positional::inner_cone_angle(
	sge::audio::scalar
)
{
}

void
sge::audio_null::positional::outer_cone_angle(
	sge::audio::scalar
)
{
}

void
sge::audio_null::positional::outer_cone_gain(
	sge::audio::scalar
)
{
}
