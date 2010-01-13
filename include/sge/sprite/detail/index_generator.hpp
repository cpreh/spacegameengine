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


#ifndef SGE_SPRITE_DETAIL_INDEX_GENERATOR_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_INDEX_GENERATOR_HPP_INCLUDED

#include <sge/sprite/detail/index_array.hpp>
#include <sge/sprite/detail/vertices_per_sprite.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

class index_generator
{
public:
	index_generator()
	:
		index(0),
		ptr(
			index_array.begin()
		)
	{
	}

	template<
		typename T
	>
	T operator()() const
	{
		T const ret(
			static_cast<
				T
			>(
				*ptr++ + index
			)
		);

		if(
			ptr == index_array.end()
		)
		{
			ptr = index_array.begin();

			index +=
				static_cast<
					index_array_type::value_type
				>(
					vertices_per_sprite
				);
		}
		return ret;
	}
private:
	mutable index_array_type::value_type index;
	mutable index_array_type::const_iterator ptr;
};

}
}
}

#endif
