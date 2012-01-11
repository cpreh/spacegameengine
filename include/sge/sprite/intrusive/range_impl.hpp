/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_INTRUSIVE_RANGE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_RANGE_IMPL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/range_decl.hpp>


template<
	typename Choices,
	bool IsConst
>
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::range(
	reference _list,
	sge::sprite::count const _size
)
:
	list_(
		_list
	),
	size_(
		_size
	)
{
}

template<
	typename Choices,
	bool IsConst
>
typename sge::sprite::intrusive::range<
	Choices,
	IsConst
>::iterator const
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::begin() const
{
	return list_.begin();
}

template<
	typename Choices,
	bool IsConst
>
typename sge::sprite::intrusive::range<
	Choices,
	IsConst
>::iterator const
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::end() const
{
	return list_.end();
}

template<
	typename Choices,
	bool IsConst
>
sge::sprite::count const
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::size() const
{
	return size_;
}

template<
	typename Choices,
	bool IsConst
>
bool
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::empty() const
{
	return list_.empty();
}

template<
	typename Choices,
	bool IsConst
>
template<
	typename Equal
>
void
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::sort(
	Equal const &_equal
) const
{
	list_.sort(
		_equal
	);
}

#endif
