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


#ifndef SGE_AUDIO_SOUND_POSITIONAL_PARAMETERS_HPP_INCLUDED
#define SGE_AUDIO_SOUND_POSITIONAL_PARAMETERS_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/sound/optional_direction.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>


namespace sge
{
namespace audio
{
namespace sound
{
/// Holds all the data necessary to construct a positional sound
/**
 * The set of positional parameters is a superset of the set of nonpositional
 * parameters.
 */
class positional_parameters
{
public:
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters();

	/// Get the position
	/** \see sge::audio::sound::positional::position */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::vector
	position() const;

	/// Set the position
	/** \see sge::audio::sound::positional::position */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	position(
		sge::audio::vector
	);

	/// Get the linear velocity
	/** \see sge::audio::sound::positional::linear_velocity */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::vector
	linear_velocity() const;

	/// Set the linear velocity
	/** \see sge::audio::sound::positional::linear_velocity */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	linear_velocity(
		sge::audio::vector
	);

	/// Get the gain
	/** \see sge::audio::sound::base::gain */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	gain() const;

	/// Set the gain
	/** \see sge::audio::sound::base::gain */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	gain(
		sge::audio::scalar
	);

	/// Get the pitch
	/** \see sge::audio::sound::base::pitch */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	pitch() const;

	/// Set the pitch
	/** \see sge::audio::sound::base::pitch */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	pitch(
		sge::audio::scalar
	);

	/// Get the rolloff factor
	/** \see sge::audio::sound::positional::rolloff_factor */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	rolloff_factor() const;

	/// Set the rolloff factor
	/** \see sge::audio::sound::positional::rolloff_factor */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	rolloff_factor(
		sge::audio::scalar
	);

	/// Get the reference distance
	/** \see sge::audio::sound::positional::reference_distance */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	reference_distance() const;

	/// Set the reference distance
	/** \see sge::audio::sound::positional::reference_distance */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	reference_distance(
		sge::audio::scalar
	);

	/// Get the maximum distance
	/** \see sge::audio::sound::positional::max_distance */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	max_distance() const;

	/// Set the maximum distance
	/** \see sge::audio::sound::positional::max_distance */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	max_distance(
		sge::audio::scalar
	);

	/// Get the direction
	/** \see sge::audio::sound::positional::direction */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::sound::optional_direction const &
	direction() const;

	/// Set the direction
	/** \see sge::audio::sound::positional::direction */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	direction(
		sge::audio::vector
	);

	/// Get the inner cone angle
	/** \see sge::audio::sound::positional::inner_cone_angle */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	inner_cone_angle() const;

	/// Set the inner cone angle
	/** \see sge::audio::sound::positional::inner_cone_angle */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	inner_cone_angle(
		sge::audio::scalar
	);

	/// Get the outer cone angle
	/** \see sge::audio::sound::positional::outer_cone_angle */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	outer_cone_angle() const;

	/// Set the outer cone angle
	/** \see sge::audio::sound::positional::outer_cone_angle */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	outer_cone_angle(
		sge::audio::scalar
	);

	/// Get the outer cone gain
	/** \see sge::audio::sound::positional::outer_cone_gain */
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	outer_cone_gain() const;

	/// Set the outer cone gain
	/** \see sge::audio::sound::positional::outer_cone_gain */
	SGE_AUDIO_DETAIL_SYMBOL
	positional_parameters &
	outer_cone_gain(
		sge::audio::scalar
	);
private:
	sge::audio::vector position_;

	sge::audio::vector linear_velocity_;

	sge::audio::scalar gain_;

	sge::audio::scalar pitch_;

	sge::audio::scalar rolloff_factor_;

	sge::audio::scalar reference_distance_;

	sge::audio::scalar max_distance_;

	sge::audio::sound::optional_direction direction_;

	sge::audio::scalar inner_cone_angle_;

	sge::audio::scalar outer_cone_angle_;

	sge::audio::scalar outer_cone_gain_;
};

}
}
}

#endif
