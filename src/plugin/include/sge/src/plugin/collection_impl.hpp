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


#ifndef SGE_SRC_PLUGIN_COLLECTION_IMPL_HPP_INCLUDED
#define SGE_SRC_PLUGIN_COLLECTION_IMPL_HPP_INCLUDED

#include <sge/plugin/category_array.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/exception.hpp>
#include <sge/plugin/iterator.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


template<
	typename Type
>
sge::plugin::collection<
	Type
>::collection(
	sge::plugin::category_array &_plugins
)
:
	plugins_(
		_plugins
	)
{
}

template<
	typename Type
>
sge::plugin::collection<
	Type
>::collection(
	collection const &_other
)
:
	plugins_(
		_other.plugins_
	)
{
}

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
>::iterator const
sge::plugin::collection<
	Type
>::begin() const
{
	return
		iterator(
			plugins_.begin()
		);
}

template<
	typename Type
>
typename
sge::plugin::collection<
	Type
>::iterator const
sge::plugin::collection<
	Type
>::end() const
{
	return
		iterator(
			plugins_.end()
		);
}

template<
	typename Type
>
typename
sge::plugin::collection<
	Type
>::context const
sge::plugin::collection<
	Type
>::get(
	size_type const _index
) const
{
	if(
		_index >= this->size()
	)
		throw sge::plugin::exception(
			FCPPT_TEXT("plugin(): No plugins found of type: \"")
			+
			fcppt::type_name(
				typeid(
					Type
				)
			)
			+
			FCPPT_TEXT("\"!")
		);

	return
		*(
			this->begin()
			+
			static_cast<
				typename iterator::difference_type
			>(
				_index
			)
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
		plugins_.size();
}

#endif
