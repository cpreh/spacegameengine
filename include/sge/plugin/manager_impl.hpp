/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "manager.hpp"
#include "../exception.hpp"
#include "../text.hpp"
#include "../iconv.hpp"

template<typename T>
sge::plugin::iterator<T>
sge::plugin::manager::begin()
{
	return iterator<T>(
		categories[detail::traits<T>::get_plugin_type()].begin());
}

template<typename T>
sge::plugin::iterator<T>
sge::plugin::manager::end()
{
	return iterator<T>(
		categories[detail::traits<T>::get_plugin_type()].end());
}

template<typename T>
typename sge::plugin::iterator<T>::reference
sge::plugin::manager::get_plugin(
	size_type const index)
{
	if(index >= size<T>())
		throw exception(
			SGE_TEXT("get_plugin(): No plugins found of type: \"")
			+ iconv(typeid(T).name())
			+ SGE_TEXT("\"!"));
	return *(begin<T>()+index);
}

template<typename T>
sge::plugin::manager::size_type
sge::plugin::manager::size() const
{
	const plugin_map::const_iterator it = categories.find(
		detail::traits<T>::get_plugin_type());
	return it == categories.end()
		? 0
		: it->second.size();
}
