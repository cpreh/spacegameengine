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


#include <sge/audio/sound/nonpositional_parameters.hpp>

sge::audio::sound::nonpositional_parameters::nonpositional_parameters()
:
	gain_(
		static_cast<audio::scalar>(
			1)),
	pitch_(
		static_cast<audio::scalar>(
			1))
{
}

sge::audio::scalar const &
sge::audio::sound::nonpositional_parameters::pitch() const
{
	return pitch_;
}

sge::audio::sound::nonpositional_parameters &
sge::audio::sound::nonpositional_parameters::pitch(
	sge::audio::scalar const &_pitch)
{
	pitch_ = _pitch;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::nonpositional_parameters::gain() const
{
	return gain_;
}

sge::audio::sound::nonpositional_parameters &
sge::audio::sound::nonpositional_parameters::gain(
	sge::audio::scalar const &_gain)
{
	gain_ = _gain;
	return *this;
}
