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


#ifndef SGE_PLUGIN_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/plugin/iterator.hpp>

template<
	typename T
>
sge::plugin::iterator<T>::iterator(
	category_array::iterator const _it
)
:
	it_(_it)
{}

template<
	typename T
>
void
sge::plugin::iterator<T>::advance(
	difference_type const _diff
)
{
	it_ += _diff;
}

template<
	typename T
>
void
sge::plugin::iterator<T>::increment()
{
	++it_;
}

template<
	typename T
>
void
sge::plugin::iterator<T>::decrement()
{
	--it_;
}

template<
	typename T
>
bool
sge::plugin::iterator<T>::equal(
	iterator const &_other
) const
{
	return it_ == _other.it_;
}

template<
	typename T
>
typename sge::plugin::iterator<T>::reference
sge::plugin::iterator<T>::dereference() const
{
	return plugin::context<T>(**it_);
}

template<
	typename T
>
typename sge::plugin::iterator<T>::difference_type
sge::plugin::iterator<T>::distance_to(
	iterator const &_other
) const
{
	return _other.it_ - it_;
}

#endif
