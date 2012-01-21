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


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_COLLECTION_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_COLLECTION_IMPL_HPP_INCLUDED

#include <sge/sprite/intrusive/collection_impl.hpp>
#include <sge/sprite/intrusive/ordered_collection_decl.hpp>


template<
	typename Choices,
	typename Order
>
sge::sprite::intrusive::ordered_collection<
	Choices,
	Order
>::ordered_collection()
:
	collections_()
{
}

template<
	typename Choices,
	typename Order
>
sge::sprite::intrusive::ordered_collection<
	Choices,
	Order
>::~ordered_collection()
{
}

template<
	typename Choices,
	typename Order
>
typename sge::sprite::intrusive::ordered_collection<
	Choices,
	Order
>::collection &
sge::sprite::intrusive::ordered_collection<
	Choices,
	Order
>::get(
	order const &_order
)
{
	return
		collections_[
			_order
		];
}

template<
	typename Choices,
	typename Order
>
typename sge::sprite::intrusive::ordered_collection<
	Choices,
	Order
>::connection_type &
sge::sprite::intrusive::ordered_collection<
	Choices,
	Order
>::connection(
	order const &_order
)
{
	return
		this->get(
			_order
		).connection();
}

template<
	typename Choices,
	typename Order
>
template<
	typename Function
>
void
sge::sprite::intrusive::ordered_collection<
	Choices,
	Order
>::for_each(
	Function const &_function
)
{
	for(
		typename order_map::iterator it(
			collections_.begin()
		);
		it != collections_.end();
		++it
	)
		_function(
			it->second->range()
		);
}

#endif
