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



#ifndef SGE_SPRITE_ANIMATION_SERIES_HPP_INCLUDED
#define SGE_SPRITE_ANIMATION_SERIES_HPP_INCLUDED

#include "animation_series_fwd.hpp"
#include "animation_entity.hpp"
#include "../renderer/dim_type.hpp"
#include "../export.hpp"
#include <vector>

namespace sge
{
namespace sprite
{

class animation_series {
public:
	typedef std::vector<
		animation_entity
	> entity_vector;
	typedef entity_vector::const_iterator const_iterator;

	SGE_SYMBOL animation_series();
	SGE_SYMBOL animation_series(
		entity_vector const&);
	SGE_SYMBOL void push_back(
		animation_entity const&);
	SGE_SYMBOL const_iterator begin() const;
	SGE_SYMBOL const_iterator end() const;
	SGE_SYMBOL bool empty() const;

	SGE_SYMBOL const renderer::dim_type dim() const;
private:
	entity_vector entities;
};

}
}

#endif
