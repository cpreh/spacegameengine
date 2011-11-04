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


#ifndef SGE_AUDIO_SOUND_POSITIONAL_HPP_INCLUDED
#define SGE_AUDIO_SOUND_POSITIONAL_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/sound/base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{
namespace sound
{
class SGE_CLASS_SYMBOL positional
:
	public base
{
	FCPPT_NONCOPYABLE(
		positional
	);
protected:
	SGE_AUDIO_SYMBOL
	positional();
public:
	SGE_AUDIO_SYMBOL
	virtual ~positional();

	virtual audio::vector const
	position() const = 0;

	virtual void
	position(
		audio::vector const &) = 0;

	virtual audio::vector const
	linear_velocity() const = 0;

	virtual void
	linear_velocity(
		audio::vector const &) = 0;

	virtual void
	rolloff(
		audio::scalar) = 0;

	virtual audio::scalar
	rolloff() const = 0;

	virtual void
	direction(
		audio::vector const &) = 0;

	virtual audio::vector const
	direction() const = 0;

	virtual void
	inner_cone_angle(
		audio::scalar) = 0;

	virtual audio::scalar
	inner_cone_angle() const = 0;

	virtual void
	outer_cone_angle(
		audio::scalar) = 0;

	virtual audio::scalar
	outer_cone_angle() const = 0;

	virtual void
	outer_cone_gain(
		audio::scalar) = 0;

	virtual audio::scalar
	outer_cone_gain() const = 0;
};
}
}
}

#endif
