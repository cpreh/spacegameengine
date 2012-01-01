/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/audio_null/positional.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sge::audio_null::positional::positional()
{
}

sge::audio_null::positional::~positional()
{
}

void
sge::audio_null::positional::play(
	sge::audio::sound::repeat::type
)
{
}

sge::audio::sound::repeat::type
sge::audio_null::positional::repeat() const
{
	return sge::audio::sound::repeat::once;
}

void
sge::audio_null::positional::toggle_pause()
{
}

sge::audio::sound::play_status::type
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
	audio::vector const &
)
{
}

void
sge::audio_null::positional::linear_velocity(
	audio::vector const &
)
{
}

void
sge::audio_null::positional::gain(
	audio::scalar
)
{
}

void
sge::audio_null::positional::pitch(
	audio::scalar
)
{
}

void
sge::audio_null::positional::rolloff_factor(
	audio::scalar
)
{
}

void
sge::audio_null::positional::reference_distance(
	audio::scalar
)
{
}

void
sge::audio_null::positional::max_distance(
	audio::scalar
)
{
}

void
sge::audio_null::positional::direction(
	audio::sound::optional_direction const &
)
{
}

void
sge::audio_null::positional::inner_cone_angle(
	audio::scalar
)
{
}

void
sge::audio_null::positional::outer_cone_angle(
	audio::scalar
)
{
}

void
sge::audio_null::positional::outer_cone_gain(
	audio::scalar
)
{
}
