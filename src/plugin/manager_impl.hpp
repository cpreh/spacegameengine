/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PLUGIN_MANAGER_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_MANAGER_IMPL_HPP_INCLUDED

#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>

template<
	typename T
>
sge::plugin::iterator<T>
sge::plugin::manager::begin()
{
	return
		iterator<T>(
			categories_[
				detail::traits<T>::plugin_type()
			].begin()
		);
}

template<
	typename T
>
sge::plugin::iterator<T>
sge::plugin::manager::end()
{
	return
		iterator<T>(
			categories_[
				detail::traits<T>::plugin_type()
			].end()
		);
}

template<
	typename T
>
sge::plugin::context<T>
sge::plugin::manager::plugin(
	size_type const _index
)
{
	if(
		_index >= size<T>()
	)
		throw sge::plugin::exception(
			FCPPT_TEXT("plugin(): No plugins found of type: \"")
			+ fcppt::type_name(typeid(T))
			+ FCPPT_TEXT("\"!")
		);

	return
		*(
			begin<T>()
			+
			static_cast<
				typename plugin::iterator<
					T
				>::difference_type
			>(
				_index
			)
		);
}

template<
	typename T
>
sge::plugin::manager::size_type
sge::plugin::manager::size() const
{
	plugin_map::const_iterator const it(
		categories_.find(
			detail::traits<T>::plugin_type()
		)
	);

	return
		it == categories_.end()
		?
			0
		:
			it->second.size();
}

#endif
