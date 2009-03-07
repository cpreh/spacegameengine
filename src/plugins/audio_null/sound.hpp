/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
namespace audio
{

class sound : public audio::sound {
public:
	sound();

	void play(sge::audio::play_mode::type);
	sge::audio::play_mode::type play_mode() const;
	void toggle_pause();
	sound_status::type status() const;
	void stop();

	point const pos() const;
	void pos(point const &);
	point const vel() const;
	void vel(point const &);
	void attenuation(unit);
	unit attenuation() const;
	void rolloff(unit);
	unit rolloff() const;
	bool positional() const;
	void positional(bool);
	void direction(point const &);
	point const direction() const;
	void inner_cone_angle(unit);
	unit inner_cone_angle() const;
	void outer_cone_angle(unit);
	unit outer_cone_angle() const;
private:
	audio::play_mode::type play_mode_;		
	audio::sound_status::type const sound_status_;
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
