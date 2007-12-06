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


#ifndef SGE_SPRITE_TEXTURE_ANIMATION_HPP_INCLUDED
#define SGE_SPRITE_TEXTURE_ANIMATION_HPP_INCLUDED

#include <vector>
#include "animation.hpp"
#include "../time.hpp"
#include "../timer.hpp"
#include "../texture/virtual_texture.hpp"

namespace sge
{

class sprite_texture_animation : public sprite_animation {
public:
	struct entity {
		entity(time_type delay, virtual_texture_ptr tex);
		const time_type           delay;
		const virtual_texture_ptr tex;
	};

	typedef std::vector<entity> animation_series;
	sprite_texture_animation(const animation_series&);

	bool process();
	void reset(sprite&);
private:
	animation_series                 series;
	timer                            cur_timer;
	sprite*                          s;
	animation_series::const_iterator pos;
};

}

#endif
