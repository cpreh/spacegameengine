/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_GEOMETRY_RANDOM_ACCESS_RANGE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_RANDOM_ACCESS_RANGE_IMPL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/geometry/random_access_range_decl.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


template<
	typename Iterator
>
sge::sprite::geometry::random_access_range<
	Iterator
>::random_access_range(
	iterator const _begin,
	iterator const _end
)
:
	begin_(
		_begin
	),
	end_(
		_end
	)
{
}

template<
	typename Iterator
>
typename sge::sprite::geometry::random_access_range<
	Iterator
>::iterator
sge::sprite::geometry::random_access_range<
	Iterator
>::begin() const
{
	return
		begin_;
}

template<
	typename Iterator
>
typename sge::sprite::geometry::random_access_range<
	Iterator
>::iterator
sge::sprite::geometry::random_access_range<
	Iterator
>::end() const
{
	return
		end_;
}

template<
	typename Iterator
>
sge::sprite::count const
sge::sprite::geometry::random_access_range<
	Iterator
>::size() const
{
	return
		sge::sprite::count(
			fcppt::cast::size<
				sge::sprite::count::value_type
			>(
				fcppt::cast::to_unsigned(
					std::distance(
						begin_,
						end_
					)
				)
			)
		);
}

template<
	typename Iterator
>
bool
sge::sprite::geometry::random_access_range<
	Iterator
>::empty() const
{
	return
		begin_ == end_;
}

template<
	typename Iterator
>
template<
	typename Compare
>
void
sge::sprite::geometry::random_access_range<
	Iterator
>::sort(
	Compare const &_compare
) const
{
	std::stable_sort(
		this->begin(),
		this->end(),
		_compare
	);
}

#endif
