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


#ifndef SGE_AUDIO_NULL_POSITIONAL_HPP_INCLUDED
#define SGE_AUDIO_NULL_POSITIONAL_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio_null
{

class positional
:
	public sge::audio::sound::positional
{
	FCPPT_NONCOPYABLE(
		positional
	);
public:
	positional();

	~positional();

	void
	play(
		sge::audio::sound::repeat::type
	);

	sge::audio::sound::repeat::type
	repeat() const;

	void
	toggle_pause();

	audio::sound::play_status::type
	status() const;

	void
	stop();

	void
	update();

	void
	position(
		audio::vector const &
	);

	void
	linear_velocity(
		audio::vector const &
	);

	void
	gain(
		audio::scalar
	);

	void
	pitch(
		audio::scalar
	);

	void
	rolloff_factor(
		audio::scalar
	);

	void
	reference_distance(
		audio::scalar
	);

	void
	max_distance(
		audio::scalar
	);

	void
	direction(
		audio::sound::optional_direction const &
	);

	void
	inner_cone_angle(
		audio::scalar
	);

	void
	outer_cone_angle(
		audio::scalar
	);

	void
	outer_cone_gain(
		audio::scalar
	);
};

}
}

#endif
