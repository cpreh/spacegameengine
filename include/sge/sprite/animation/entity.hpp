/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/sprite/animation/entity_fwd.hpp>
#include <sge/time/unit.hpp>
#include <sge/time/duration.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace sprite
{
namespace animation
{

class entity
{
public:
	SGE_SYMBOL entity(
		time::duration const &delay,
		sge::texture::const_part_ptr tex
	);

	SGE_SYMBOL time::unit
	delay() const;

	SGE_SYMBOL sge::texture::const_part_ptr const
	tex() const;

	SGE_SYMBOL void
	tex(
		sge::texture::const_part_ptr
	);

	SGE_SYMBOL renderer::dim_type const
	dim() const;
private:
	time::unit delay_;
	sge::texture::const_part_ptr tex_;
};

}
}
}

#endif
