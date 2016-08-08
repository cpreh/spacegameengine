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


#ifndef SGE_IMAGE_IMPL_STORE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STORE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/store/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename ElementsWrapper
>
template<
	typename Element,
	typename
>
sge::image::store::object<
	ElementsWrapper
>::object(
	Element &&_element
)
:
	variant_(
		std::move(
			_element
		)
	)
{
}

template<
	typename ElementsWrapper
>
sge::image::store::object<
	ElementsWrapper
>::object(
	object const &
) = default;

template<
	typename ElementsWrapper
>
sge::image::store::object<
	ElementsWrapper
>::object(
	object &&
) = default;

template<
	typename ElementsWrapper
>
sge::image::store::object<
	ElementsWrapper
> &
sge::image::store::object<
	ElementsWrapper
>::operator=(
	object const &
) = default;

template<
	typename ElementsWrapper
>
sge::image::store::object<
	ElementsWrapper
> &
sge::image::store::object<
	ElementsWrapper
>::operator=(
	object &&
) = default;

template<
	typename ElementsWrapper
>
sge::image::store::object<
	ElementsWrapper
>::~object()
{
}

template<
	typename ElementsWrapper
>
typename
sge::image::store::object<
	ElementsWrapper
>::variant &
sge::image::store::object<
	ElementsWrapper
>::get()
{
	return
		variant_;
}

template<
	typename ElementsWrapper
>
typename
sge::image::store::object<
	ElementsWrapper
>::variant const &
sge::image::store::object<
	ElementsWrapper
>::get() const
{
	return
		variant_;
}

#endif
