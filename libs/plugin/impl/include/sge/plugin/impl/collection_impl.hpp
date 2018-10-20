/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PLUGIN_IMPL_COLLECTION_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_COLLECTION_IMPL_HPP_INCLUDED

#include <sge/plugin/category_array.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <fcppt/reference_impl.hpp>


template<
	typename Type
>
sge::plugin::collection<
	Type
>::collection(
	sge::plugin::category_array const &_plugins
)
:
	plugins_{
		_plugins
	}
{
}

template<
	typename Type
>
sge::plugin::collection<
	Type
>::collection(
	collection const &
)
=
default;

template<
	typename Type
>
sge::plugin::collection<
	Type
> &
sge::plugin::collection<
	Type
>::operator=(
	collection const &
)
=
default;

template<
	typename Type
>
sge::plugin::collection<
	Type
>::~collection()
{
}

template<
	typename Type
>
typename
sge::plugin::collection<
	Type
>::iterator
sge::plugin::collection<
	Type
>::begin() const
{
	return
		iterator(
			plugins_.get().begin()
		);
}

template<
	typename Type
>
typename
sge::plugin::collection<
	Type
>::iterator
sge::plugin::collection<
	Type
>::end() const
{
	return
		iterator(
			plugins_.get().end()
		);
}

template<
	typename Type
>
typename
sge::plugin::collection<
	Type
>::size_type
sge::plugin::collection<
	Type
>::size() const
{
	return
		plugins_.get().size();
}

#endif
