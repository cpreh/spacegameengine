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


#ifndef SGE_SPRITE_ANIMATION_ENTITY_HPP_INCLUDED
#define SGE_SPRITE_ANIMATION_ENTITY_HPP_INCLUDED

#include "../time/types.hpp"
#include "../export.hpp"
#include "../texture/part.hpp"
#include "../renderer/texture.hpp"

namespace sge
{
namespace sprite
{

class animation_entity {
public:
	SGE_SYMBOL animation_entity(
		time::resolution const& delay,
		texture::part_ptr tex);
	SGE_SYMBOL time::unit delay() const;
	SGE_SYMBOL const texture::part_ptr tex() const;
	SGE_SYMBOL const renderer::texture::dim_type dim() const;
private:
	time::unit          delay_;
	texture::part_ptr   tex_;
};

}
}

#endif
