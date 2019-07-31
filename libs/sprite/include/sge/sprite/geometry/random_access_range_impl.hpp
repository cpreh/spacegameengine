//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
sge::sprite::count
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
