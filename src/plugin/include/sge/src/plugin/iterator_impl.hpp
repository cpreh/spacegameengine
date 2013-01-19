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


#ifndef SGE_SRC_PLUGIN_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_SRC_PLUGIN_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/plugin/category_array.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>


template<
	typename Type
>
sge::plugin::iterator<
	Type
>::iterator(
	sge::plugin::category_array::iterator const _it
)
:
	it_(
		_it
	)
{
}

template<
	typename Type
>
void
sge::plugin::iterator<
	Type
>::advance(
	difference_type const _diff
)
{
	it_ += _diff;
}

template<
	typename Type
>
void
sge::plugin::iterator<
	Type
>::increment()
{
	++it_;
}

template<
	typename Type
>
void
sge::plugin::iterator<
	Type
>::decrement()
{
	--it_;
}

template<
	typename Type
>
bool
sge::plugin::iterator<
	Type
>::equal(
	iterator const &_other
) const
{
	return
		it_ == _other.it_;
}

template<
	typename Type
>
typename sge::plugin::iterator<
	Type
>::reference
sge::plugin::iterator<
	Type
>::dereference() const
{
	return
		sge::plugin::context<
			Type
		>(
			**it_
		);
}

template<
	typename Type
>
typename sge::plugin::iterator<
	Type
>::difference_type
sge::plugin::iterator<
	Type
>::distance_to(
	iterator const &_other
) const
{
	return
		_other.it_ - it_;
}

#endif
