/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PROJECTILE_DETAIL_TRIANGLE_SET_HASH_HPP_INCLUDED
#define SGE_PROJECTILE_DETAIL_TRIANGLE_SET_HASH_HPP_INCLUDED

#include <sge/projectile/triangle.hpp>
#include <boost/functional/hash/hash.hpp>
#include <cstddef>

namespace sge
{
namespace projectile
{
namespace detail
{
class triangle_set_hash
{
public:
	std::size_t
	operator()(
		triangle const &_value
	) const
	{
		std::size_t result = 0;

		for(
			triangle::const_iterator point_it(
				_value.begin()
			);
			point_it != _value.end();
			++point_it
		)
			for(
				triangle::value_type::const_iterator point_component_it(
					point_it->begin()
				);
				point_component_it != point_it->end();
				++point_component_it
			)
				result ^= 
					boost::hash_value(
						*point_component_it
					)
					+ 0x9e3779b9
					+ (result<<6) + (result>>2);

		return result;
	}
};
}
}
}

#endif
