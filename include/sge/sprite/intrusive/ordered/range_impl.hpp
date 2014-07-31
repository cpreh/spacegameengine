/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_IMPL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/detail/ordered_range_size.hpp>
#include <sge/sprite/intrusive/ordered/iterator_impl.hpp>
#include <sge/sprite/intrusive/ordered/range_decl.hpp>


template<
	typename Choices,
	typename Order,
	bool IsConst
>
sge::sprite::intrusive::ordered::range<
	Choices,
	Order,
	IsConst
>::range(
	ordered_map_reference _ordered_map
)
:
	ordered_map_(
		_ordered_map
	),
	size_(
		sge::sprite::intrusive::detail::ordered_range_size<
			Order,
			Choices
		>(
			_ordered_map
		)
	)
{
}

template<
	typename Choices,
	typename Order,
	bool IsConst
>
typename sge::sprite::intrusive::ordered::range<
	Choices,
	Order,
	IsConst
>::iterator const
sge::sprite::intrusive::ordered::range<
	Choices,
	Order,
	IsConst
>::begin() const
{
	return
		iterator(
			ordered_map_.begin(),
			ordered_map_.end()
		);
}

template<
	typename Choices,
	typename Order,
	bool IsConst
>
typename sge::sprite::intrusive::ordered::range<
	Choices,
	Order,
	IsConst
>::iterator const
sge::sprite::intrusive::ordered::range<
	Choices,
	Order,
	IsConst
>::end() const
{
	return
		iterator(
			ordered_map_.end(),
			ordered_map_.end()
		);
}

template<
	typename Choices,
	typename Order,
	bool IsConst
>
sge::sprite::count const
sge::sprite::intrusive::ordered::range<
	Choices,
	Order,
	IsConst
>::size() const
{
	return
		size_;
}

template<
	typename Choices,
	typename Order,
	bool IsConst
>
bool
sge::sprite::intrusive::ordered::range<
	Choices,
	Order,
	IsConst
>::empty() const
{
	return
		size_.get() == 0u;
}

template<
	typename Choices,
	typename Order,
	bool IsConst
>
template<
	typename Equal
>
void
sge::sprite::intrusive::ordered::range<
	Choices,
	Order,
	IsConst
>::sort(
	Equal const &_func
) const
{
	for(
		auto const &element
		:
		ordered_map_
	)
		element.second->range().sort(
			_func
		);
}

#endif
