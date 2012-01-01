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


#ifndef SGE_AUDIO_SOUND_POSITIONAL_PARAMETERS_HPP_INCLUDED
#define SGE_AUDIO_SOUND_POSITIONAL_PARAMETERS_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/sound/optional_direction.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


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
	SGE_AUDIO_SYMBOL explicit
	positional_parameters();

	/// Get the position
	/** \see sge::audio::sound::positional::position */
	SGE_AUDIO_SYMBOL audio::vector const &
	position() const;

	/// Set the position
	/** \see sge::audio::sound::positional::position */
	SGE_AUDIO_SYMBOL positional_parameters &
	position(
		audio::vector const &);

	/// Get the linear velocity
	/** \see sge::audio::sound::positional::linear_velocity */
	SGE_AUDIO_SYMBOL audio::vector const &
	linear_velocity() const;

	/// Set the linear velocity
	/** \see sge::audio::sound::positional::linear_velocity */
	SGE_AUDIO_SYMBOL positional_parameters &
	linear_velocity(
		audio::vector const &);

	/// Get the gain
	/** \see sge::audio::sound::base::gain */
	SGE_AUDIO_SYMBOL audio::scalar const &
	gain() const;

	/// Set the gain
	/** \see sge::audio::sound::base::gain */
	SGE_AUDIO_SYMBOL positional_parameters &
	gain(
		audio::scalar const &);

	/// Get the pitch
	/** \see sge::audio::sound::base::pitch */
	SGE_AUDIO_SYMBOL audio::scalar const &
	pitch() const;

	/// Set the pitch
	/** \see sge::audio::sound::base::pitch */
	SGE_AUDIO_SYMBOL positional_parameters &
	pitch(
		audio::scalar const &);

	/// Get the rolloff factor
	/** \see sge::audio::sound::positional::rolloff_factor */
	SGE_AUDIO_SYMBOL audio::scalar const &
	rolloff_factor() const;

	/// Set the rolloff factor
	/** \see sge::audio::sound::positional::rolloff_factor */
	SGE_AUDIO_SYMBOL positional_parameters &
	rolloff_factor(
		audio::scalar const &);

	/// Get the reference distance
	/** \see sge::audio::sound::positional::reference_distance */
	SGE_AUDIO_SYMBOL audio::scalar const &
	reference_distance() const;

	/// Set the reference distance
	/** \see sge::audio::sound::positional::reference_distance */
	SGE_AUDIO_SYMBOL positional_parameters &
	reference_distance(
		audio::scalar const &);

	/// Get the maximum distance
	/** \see sge::audio::sound::positional::max_distance */
	SGE_AUDIO_SYMBOL audio::scalar const &
	max_distance() const;

	/// Set the maximum distance
	/** \see sge::audio::sound::positional::max_distance */
	SGE_AUDIO_SYMBOL positional_parameters &
	max_distance(
		audio::scalar const &);

	/// Get the direction
	/** \see sge::audio::sound::positional::direction */
	SGE_AUDIO_SYMBOL sound::optional_direction const &
	direction() const;

	/// Set the direction
	/** \see sge::audio::sound::positional::direction */
	SGE_AUDIO_SYMBOL positional_parameters &
	direction(
		audio::vector const &);

	/// Get the inner cone angle
	/** \see sge::audio::sound::positional::inner_cone_angle */
	SGE_AUDIO_SYMBOL audio::scalar const &
	inner_cone_angle() const;

	/// Set the inner cone angle
	/** \see sge::audio::sound::positional::inner_cone_angle */
	SGE_AUDIO_SYMBOL positional_parameters &
	inner_cone_angle(
		audio::scalar const &);

	/// Get the outer cone angle
	/** \see sge::audio::sound::positional::outer_cone_angle */
	SGE_AUDIO_SYMBOL audio::scalar const &
	outer_cone_angle() const;

	/// Set the outer cone angle
	/** \see sge::audio::sound::positional::outer_cone_angle */
	SGE_AUDIO_SYMBOL positional_parameters &
	outer_cone_angle(
		audio::scalar const &);

	/// Get the outer cone gain
	/** \see sge::audio::sound::positional::outer_cone_gain */
	SGE_AUDIO_SYMBOL audio::scalar const &
	outer_cone_gain() const;

	/// Set the outer cone gain
	/** \see sge::audio::sound::positional::outer_cone_gain */
	SGE_AUDIO_SYMBOL positional_parameters &
	outer_cone_gain(
		audio::scalar const &);
private:
	audio::vector position_;
	audio::vector linear_velocity_;
	audio::scalar gain_;
	audio::scalar pitch_;
	audio::scalar rolloff_factor_;
	audio::scalar reference_distance_;
	audio::scalar max_distance_;
	sound::optional_direction direction_;
	audio::scalar inner_cone_angle_;
	audio::scalar outer_cone_angle_;
	audio::scalar outer_cone_gain_;
};
}
}
}

#endif
