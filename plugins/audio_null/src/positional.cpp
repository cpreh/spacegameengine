//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/scalar.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/sound/optional_direction_fwd.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/audio_null/positional.hpp>


sge::audio_null::positional::positional()
= default;

sge::audio_null::positional::~positional()
= default;

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
