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


#ifndef SGE_SRC_PLUGIN_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SRC_PLUGIN_OBJECT_IMPL_HPP_INCLUDED

#include <sge/plugin/object.hpp>
#include <sge/plugin/detail/traits.hpp>
#include <sge/src/plugin/library/load_function.hpp>
#include <sge/src/plugin/library/object.hpp>


template<
	typename Type
>
sge::plugin::object<
	Type
>::object(
	library_shared_ptr const &_lib
)
:
	lib_(
		_lib
	),
	loader_(
		sge::plugin::library::load_function<
			loader_fun
		>(
			*lib_,
			sge::plugin::detail::traits<
				Type
			>::plugin_loader_name()
		)
	)
{
}

template<
	typename Type
>
sge::plugin::object<
	Type
>::object(
	object &&
) = default;

template<
	typename Type
>
sge::plugin::object<
	Type
> &
sge::plugin::object<
	Type
>::operator=(
	object &&
) = default;

template<
	typename Type
>
sge::plugin::object<
	Type
>::~object()
{
}

template<
	typename Type
>
typename sge::plugin::object<
	Type
>::loader_fun
sge::plugin::object<
	Type
>::get() const
{
	return
		loader_;
}

#endif
