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
namespace sprite
{

class texture_animation : public animation {
public:
	struct entity {
		entity(time_type delay, virtual_texture_ptr tex);
		time_type           delay;
		virtual_texture_ptr tex;
	};

	struct loop_method {
		enum type {
			repeat,
			stop_after_end,
			stop_at_end
		};
	};

	typedef std::vector<entity> animation_series;
	texture_animation(
		const animation_series&,
		loop_method::type,
		object *init_sprite = 0);
	
	void bind(object*);
	bool process();
	void reset();

	const texture::dim_type dim() const;
private:
	animation_series                 series;
	loop_method::type                action;
	timer                            cur_timer;
	object*                          s;
	animation_series::const_iterator pos;
};

}
}

#endif
