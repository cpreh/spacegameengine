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


#ifndef SGE_AUDIO_NULL_SOUND_HPP_INCLUDED
#define SGE_AUDIO_NULL_SOUND_HPP_INCLUDED

#include <sge/audio/sound.hpp>
#include <sge/math/vector/basic_decl.hpp>

namespace sge
{
namespace audio_null
{

class sound : public audio::sound {
public:
	sound();

	void play(audio::play_mode::type);
	audio::play_mode::type play_mode() const;
	void toggle_pause();
	audio::sound_status::type status() const;
	void stop();

	audio::point const pos() const;
	void pos(audio::point const &);
	audio::point const vel() const;
	void vel(audio::point const &);
	void attenuation(audio::unit);
	audio::unit attenuation() const;
	void rolloff(audio::unit);
	audio::unit rolloff() const;
	bool positional() const;
	void positional(bool);
	void direction(audio::point const &);
	audio::point const direction() const;
	void inner_cone_angle(audio::unit);
	audio::unit inner_cone_angle() const;
	void outer_cone_angle(audio::unit);
	audio::unit outer_cone_angle() const;
private:
	audio::play_mode::type play_mode_;		
	audio::sound_status::type const status_;
	audio::point
		pos_,
		vel_;
	audio::unit
		attenuation_,
		rolloff_;
	bool positional_;
	audio::point direction_;
	audio::unit
		inner_cone_angle_,
		outer_cone_angle_;
};

}
}

#endif
