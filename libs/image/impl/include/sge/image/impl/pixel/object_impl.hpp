//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_PIXEL_OBJECT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_PIXEL_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/pixel/object.hpp>


template<
	typename Tag
>
sge::image::pixel::object<
	Tag
>::object(
	variant const &_variant
)
:
	variant_{
		_variant
	}
{
}

template<
	typename Tag
>
sge::image::pixel::object<
	Tag
>::object(
	object const &
)
= default;

template<
	typename Tag
>
sge::image::pixel::object<
	Tag
>::object(
	object &&
)
noexcept
= default;

template<
	typename Tag
>
sge::image::pixel::object<
	Tag
> &
sge::image::pixel::object<
	Tag
>::operator=(
	object const &
)
= default;

template<
	typename Tag
>
sge::image::pixel::object<
	Tag
> &
sge::image::pixel::object<
	Tag
>::operator=(
	object &&
)
noexcept
= default;

template<
	typename Tag
>
sge::image::pixel::object<
	Tag
>::~object()
= default;

template<
	typename Tag
>
typename
sge::image::pixel::object<
	Tag
>::variant const &
sge::image::pixel::object<
	Tag
>::get() const
{
	return
		variant_;
}

#endif
