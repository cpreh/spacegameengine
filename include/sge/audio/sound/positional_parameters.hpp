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


#ifndef SGE_AUDIO_SOUND_POSITIONAL_PARAMETERS_HPP_INCLUDED
#define SGE_AUDIO_SOUND_POSITIONAL_PARAMETERS_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


namespace sge
{
namespace audio
{
namespace sound
{
class positional_parameters
{
public:
	SGE_AUDIO_SYMBOL explicit
	positional_parameters();

	SGE_AUDIO_SYMBOL audio::vector const &
	position() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	position(
		audio::vector const &);

	SGE_AUDIO_SYMBOL audio::vector const &
	linear_velocity() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	linear_velocity(
		audio::vector const &);

	SGE_AUDIO_SYMBOL audio::scalar const &
	gain() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	gain(
		audio::scalar const &);

	SGE_AUDIO_SYMBOL audio::scalar const &
	pitch() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	pitch(
		audio::scalar const &);

	SGE_AUDIO_SYMBOL audio::scalar const &
	rolloff() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	rolloff(
		audio::scalar const &);

	SGE_AUDIO_SYMBOL audio::vector const &
	direction() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	direction(
		audio::vector const &);

	SGE_AUDIO_SYMBOL audio::scalar const &
	inner_cone_angle() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	inner_cone_angle(
		audio::scalar const &);

	SGE_AUDIO_SYMBOL audio::scalar const &
	outer_cone_angle() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	outer_cone_angle(
		audio::scalar const &);

	SGE_AUDIO_SYMBOL audio::scalar const &
	outer_cone_gain() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	outer_cone_gain(
		audio::scalar const &);
private:
	audio::vector position_;
	audio::vector linear_velocity_;
	audio::scalar gain_;
	audio::scalar pitch_;
	audio::scalar rolloff_;
	audio::vector direction_;
	audio::scalar inner_cone_angle_;
	audio::scalar outer_cone_angle_;
	audio::scalar outer_cone_gain_;
};
}
}
}

#endif
