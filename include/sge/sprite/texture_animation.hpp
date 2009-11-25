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


#ifndef SGE_SPRITE_TEXTURE_ANIMATION_HPP_INCLUDED
#define SGE_SPRITE_TEXTURE_ANIMATION_HPP_INCLUDED

#include <sge/sprite/animation.hpp>
#include <sge/sprite/animation_series.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/fun.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace sprite
{

class object;

class SGE_CLASS_SYMBOL texture_animation : public animation {
public:
	class loop_method {
	public:
		enum type {
			repeat,
			stop_at_end
		};
	};

	SGE_SYMBOL texture_animation(
		animation_series const &,
		loop_method::type,
		object &init_sprite,
		time::fun const &time_fun
			= time::default_time_fun());

	SGE_SYMBOL bool process();
	SGE_SYMBOL void reset();

	SGE_SYMBOL
	animation_series const &
	series() const;
private:
	animation_series series_;
	loop_method::type action;
	time::timer cur_timer;
	object &spr;
	animation_series::const_iterator pos;
};

}
}

#endif
