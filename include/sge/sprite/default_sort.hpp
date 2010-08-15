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


#ifndef SGE_SPRITE_DEFAULT_SORT_HPP_INCLUDED
#define SGE_SPRITE_DEFAULT_SORT_HPP_INCLUDED

#include <sge/sprite/default_compare.hpp>
#include <sge/sprite/with_depth.hpp>
#include <sge/sprite/with_texture.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <algorithm>
#include <iterator>

namespace sge
{
namespace sprite
{

struct default_sort
{
	template<
		typename In
	>
	typename boost::enable_if<
		boost::mpl::or_<
			boost::mpl::contains<
				typename std::iterator_traits<
					In
				>::value_type::elements,
				with_texture
			>,
			boost::mpl::contains<
				typename std::iterator_traits<
					In
				>::value_type::elements,
				with_depth
			>
		>,
		void
	>::type
	operator()(
		In const beg,
		In const end
	)  const
	{
		std::stable_sort(
			beg,
			end,
			default_compare()
		);
	}
};

}
}

#endif
