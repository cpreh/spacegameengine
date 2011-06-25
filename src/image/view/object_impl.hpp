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


#ifndef SGE_IMAGE_VIEW_OBJECT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_VIEW_OBJECT_IMPL_HPP_INCLUDED

#define SGE_IMAGE_INSTANTIATE_EXPORTS
#include <sge/image/view/object.hpp>
#undef SGE_IMAGE_INSTANTIATE_EXPORTS
#include <fcppt/variant/object_impl.hpp>

template<
	typename ElementsWrapper
>
sge::image::view::object<ElementsWrapper>::object(
	variant const &_variant
)
:
	variant_(_variant)
{
}

template<
	typename ElementsWrapper
>
sge::image::view::object<ElementsWrapper>::object(
	object const &_other
)
:
	variant_(_other.variant_)
{
}

template<
	typename ElementsWrapper
>
sge::image::view::object<ElementsWrapper> &
sge::image::view::object<ElementsWrapper>::operator=(
	object const &_other
)
{
	if(
		this != &_other
	)
		variant_ = _other.variant_;
	
	return *this;
}

template<
	typename ElementsWrapper
>
sge::image::view::object<ElementsWrapper>::~object()
{
}

template<
	typename ElementsWrapper
>
typename sge::image::view::object<ElementsWrapper>::variant const &
sge::image::view::object<ElementsWrapper>::get() const
{
	return variant_;
}

#endif
