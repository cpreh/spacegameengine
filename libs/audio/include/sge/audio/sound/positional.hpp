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


#ifndef SGE_AUDIO_SOUND_POSITIONAL_HPP_INCLUDED
#define SGE_AUDIO_SOUND_POSITIONAL_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/optional_direction_fwd.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{
namespace sound
{

/// The base class for positional (3D) sounds (streaming, nonstreaming)
/**
 * This class is an interface class, you cannot instantiate it. Audio plugins
 * (OpenAL, DirectSound) must derive from this class.
 *
 * For an introduction to positional sounds, see \ref audio_positional.
 */
class SGE_CORE_DETAIL_CLASS_SYMBOL positional
:
	public sge::audio::sound::base
{
	FCPPT_NONCOPYABLE(
		positional
	);
protected:
	SGE_AUDIO_DETAIL_SYMBOL
	positional();
public:
	SGE_AUDIO_DETAIL_SYMBOL
	~positional()
	override;

	/// Sets the 3D position
	virtual
	void
	position(
		sge::audio::vector const &
	) = 0;

	/// Sets the linear velocity (used for Doppler calculations) (see \ref audio_positional)
	virtual
	void
	linear_velocity(
		sge::audio::vector const &
	) = 0;

	/// Sets the rolloff factor (see \ref audio_positional)
	virtual
	void
	rolloff_factor(
		sge::audio::scalar
	) = 0;

	/// Sets the reference distance (see \ref audio_positional)
	virtual
	void
	reference_distance(
		sge::audio::scalar
	) = 0;

	/// Sets the maximum distance (see \ref audio_positional)
	virtual
	void
	max_distance(
		sge::audio::scalar
	) = 0;

	/// Sets the direction distance (see \ref audio_positional)
	virtual
	void
	direction(
		sge::audio::sound::optional_direction const &
	) = 0;

	/// Sets the inner cone angle (see \ref audio_positional)
	virtual
	void
	inner_cone_angle(
		sge::audio::scalar
	) = 0;

	/// Sets the outer cone angle (see \ref audio_positional)
	virtual
	void
	outer_cone_angle(
		sge::audio::scalar
	) = 0;

	/// Sets the outer cone gain (see \ref audio_positional)
	virtual
	void
	outer_cone_gain(
		sge::audio::scalar
	) = 0;
};

}
}
}

#endif
