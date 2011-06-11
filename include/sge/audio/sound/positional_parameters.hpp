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

#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/symbol.hpp>
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

	SGE_AUDIO_SYMBOL vector const &
	position() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	position(
		vector const &);

	SGE_AUDIO_SYMBOL vector const &
	linear_velocity() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	linear_velocity(
		vector const &);

	SGE_AUDIO_SYMBOL scalar const &
	gain() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	gain(
		scalar const &);

	SGE_AUDIO_SYMBOL scalar const &
	rolloff() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	rolloff(
		scalar const &);

	SGE_AUDIO_SYMBOL vector const &
	direction() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	direction(
		vector const &);

	SGE_AUDIO_SYMBOL scalar const &
	inner_cone_angle() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	inner_cone_angle(
		scalar const &);

	SGE_AUDIO_SYMBOL scalar const &
	outer_cone_angle() const;

	SGE_AUDIO_SYMBOL positional_parameters &
	outer_cone_angle(
		scalar const &);
private:
	vector position_;
	vector linear_velocity_;
	scalar gain_;
	scalar rolloff_;
	vector direction_;
	scalar inner_cone_angle_;
	scalar outer_cone_angle_;
};
}
}
}

#endif
