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


#ifndef SGE_SRC_IMAGE_VIEW_CONST_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_VIEW_CONST_OBJECT_IMPL_HPP_INCLUDED

#define SGE_IMAGE_INSTANTIATE_EXPORTS
#include <sge/image/view/const_object.hpp>
#undef SGE_IMAGE_INSTANTIATE_EXPORTS
#include <sge/image/view/to_const.hpp>
#include <fcppt/variant/object_impl.hpp>


template<
	typename ElementsWrapper,
	typename NonConstElementsWrapper
>
sge::image::view::const_object<
	ElementsWrapper,
	NonConstElementsWrapper
>::const_object(
	variant const &_variant
)
:
	variant_(_variant)
{
}

template<
	typename ElementsWrapper,
	typename NonConstElementsWrapper
>
sge::image::view::const_object<
	ElementsWrapper,
	NonConstElementsWrapper
>::const_object(
	nonconst_object const &_other
)
:
	variant_(
		image::view::to_const<
			typename ElementsWrapper::tag
		>(
			_other
		).get()
	)
{
}

template<
	typename ElementsWrapper,
	typename NonConstElementsWrapper
>
sge::image::view::const_object<
	ElementsWrapper,
	NonConstElementsWrapper
>::const_object(
	const_object const &_other
)
:
	variant_(_other.variant_)
{
}

template<
	typename ElementsWrapper,
	typename NonConstElementsWrapper
>
sge::image::view::const_object<
	ElementsWrapper,
	NonConstElementsWrapper
> &
sge::image::view::const_object<
	ElementsWrapper,
	NonConstElementsWrapper
>::operator=(
	const_object const &_other
)
{
	if(
		this != &_other
	)
		variant_ = _other.variant_;

	return *this;
}

template<
	typename ElementsWrapper,
	typename NonConstElementsWrapper
>
sge::image::view::const_object<
	ElementsWrapper,
	NonConstElementsWrapper
>::~const_object()
{
}

template<
	typename ElementsWrapper,
	typename NonConstElementsWrapper
>
typename sge::image::view::const_object<
	ElementsWrapper,
	NonConstElementsWrapper
>::variant const &
sge::image::view::const_object<
	ElementsWrapper,
	NonConstElementsWrapper
>::get() const
{
	return variant_;
}

#endif
