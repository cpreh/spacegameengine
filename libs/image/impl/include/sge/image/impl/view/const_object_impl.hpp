//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_CONST_OBJECT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_CONST_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/to_const.hpp>


template<
	typename Tag
>
sge::image::view::const_object<
	Tag
>::const_object(
	variant const &_variant
)
:
	variant_(
		_variant
	)
{
}

template<
	typename Tag
>
sge::image::view::const_object<
	Tag
>::const_object(
	nonconst_object const &_other
)
:
	variant_(
		sge::image::view::to_const<
			Tag
		>(
			_other
		).get()
	)
{
}

template<
	typename Tag
>
sge::image::view::const_object<
	Tag
>::const_object(
	const_object const &
)
= default;

template<
	typename Tag
>
sge::image::view::const_object<
	Tag
>::const_object(
	const_object &&
)
noexcept
= default;

template<
	typename Tag
>
sge::image::view::const_object<
	Tag
> &
sge::image::view::const_object<
	Tag
>::operator=(
	const_object const &
)
= default;

template<
	typename Tag
>
sge::image::view::const_object<
	Tag
> &
sge::image::view::const_object<
	Tag
>::operator=(
	const_object &&
)
noexcept
= default;

template<
	typename Tag
>
sge::image::view::const_object<
	Tag
>::~const_object<
	Tag
>()
= default;

template<
	typename Tag
>
typename
sge::image::view::const_object<
	Tag
>::variant const &
sge::image::view::const_object<
	Tag
>::get() const
{
	return
		variant_;
}

#endif
