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


#ifndef SGE_SPRITE_ANIMATION_SERIES_HPP_INCLUDED
#define SGE_SPRITE_ANIMATION_SERIES_HPP_INCLUDED

#include <sge/sprite/animation/series_fwd.hpp>
#include <sge/sprite/animation/entity.hpp>
#include <sge/sprite/animation/entity_vector.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/symbol.hpp>
#include <vector>

namespace sge
{
namespace sprite
{
namespace animation
{

class series
{
public:
	typedef entity_vector::const_iterator const_iterator;

	SGE_SYMBOL series();

	SGE_SYMBOL explicit series(
		entity_vector const &
	);

	SGE_SYMBOL void
	push_back(
		entity const &
	);

	SGE_SYMBOL entity_vector &
	entities();

	SGE_SYMBOL entity_vector const &
	entities() const;

	SGE_SYMBOL const_iterator
	begin() const;

	SGE_SYMBOL const_iterator
	end() const;

	SGE_SYMBOL bool
	empty() const;
private:
	entity_vector entities_;
};

}
}
}

#endif
