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


#include "../texture_animation.hpp"
#include "../sprite.hpp"

sge::sprite_texture_animation::sprite_texture_animation(const animation_series& series_)
: series(series_),
  cur_timer(0),
  s(0),
  pos(series.end())
{}

bool sge::sprite_texture_animation::process()
{
	if(!s || pos == series.end())
		return false;
	if(cur_timer.expired())
	{
		++pos;
		if(pos == series.end())
			return false;
		set_frame(pos);
	}
	return true;
}

void sge::sprite_texture_animation::reset(sprite& nspr)
{
	s = &nspr;
	pos = series.begin();
	set_frame(pos);
}

void sge::sprite_texture_animation::set_frame(const animation_series::const_iterator it)
{
	cur_timer.interval(it->delay);
	s->set_texture(it->tex);
}

sge::sprite_texture_animation::entity::entity(const time_type delay,
                                              const virtual_texture_ptr tex)
: delay(delay),
  tex(tex)
{}
