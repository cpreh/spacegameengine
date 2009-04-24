/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include "../sound.hpp"
#include <sge/math/vector/basic_impl.hpp>

sge::audio_null::sound::sound()
:
	play_mode_(
		audio::play_mode::once
	),
	status_(
		audio::sound_status::stopped
	),
	pos_(
		audio::point::null()
	),
	vel_(
		audio::point::null()
	),
	attenuation_(
		static_cast<audio::unit>(0)
	),
	rolloff_(
		static_cast<audio::unit>(0)
	),
	positional_(
		false
	),
	direction_(
		audio::point::null()
	),
	inner_cone_angle_(
		static_cast<audio::unit>(0)
	),
	outer_cone_angle_(
		static_cast<audio::unit>(0)
	)
{}

void
sge::audio_null::sound::play(
	sge::audio::play_mode::type const nplay_mode)
{
	play_mode_ = nplay_mode;	
}

sge::audio::play_mode::type
sge::audio_null::sound::play_mode() const
{
	return play_mode_;
}

void
sge::audio_null::sound::toggle_pause()
{
}

sge::audio::sound_status::type
sge::audio_null::sound::status() const
{
	return status_;
}

void
sge::audio_null::sound::stop()
{
}


sge::audio::point const
sge::audio_null::sound::pos() const
{
	return pos_;
}

void
sge::audio_null::sound::pos(
	audio::point const &npos)
{
	pos_ = npos;
}

sge::audio::point const
sge::audio_null::sound::vel() const
{
	return vel_;
}

void
sge::audio_null::sound::vel(
	audio::point const &nvel)
{
	vel_ = nvel;
}

void
sge::audio_null::sound::attenuation(
	audio::unit const nattenuation)
{
	attenuation_ = nattenuation;
}

sge::audio::unit
sge::audio_null::sound::attenuation() const
{
	return attenuation_;
}

void
sge::audio_null::sound::rolloff(
	audio::unit const nrolloff)
{
	rolloff_ = nrolloff;
}

sge::audio::unit
sge::audio_null::sound::rolloff() const
{
	return rolloff_;
}

bool
sge::audio_null::sound::positional() const
{
	return positional_;
}

void
sge::audio_null::sound::positional(
	bool const npositional)
{
	positional_ = npositional;
}

void
sge::audio_null::sound::direction(
	audio::point const &ndirection)
{
	direction_ = ndirection;
}

sge::audio::point const
sge::audio_null::sound::direction() const
{
	return direction_;
}

void
sge::audio_null::sound::inner_cone_angle(
	audio::unit const ninner_cone_angle)
{
	inner_cone_angle_ = ninner_cone_angle;
}

sge::audio::unit
sge::audio_null::sound::inner_cone_angle() const
{
	return inner_cone_angle_;
}

void
sge::audio_null::sound::outer_cone_angle(
	audio::unit const nouter_cone_angle)
{
	outer_cone_angle_ = nouter_cone_angle;
}

sge::audio::unit
sge::audio_null::sound::outer_cone_angle() const
{
	return outer_cone_angle_;
}
