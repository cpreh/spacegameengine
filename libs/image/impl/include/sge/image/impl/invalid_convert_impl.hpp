//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_INVALID_CONVERT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_INVALID_CONVERT_IMPL_HPP_INCLUDED

#include <sge/image/exception.hpp>
#include <sge/image/invalid_convert.hpp>
#include <sge/image/traits/pixel/format_to_string.hpp>
#include <fcppt/text.hpp>


template<
	typename Tag
>
sge::image::invalid_convert<
	Tag
>::invalid_convert(
	format const _source,
	format const _dest
)
:
	sge::image::exception{
		FCPPT_TEXT("Invalid image convert from ")
		+
		sge::image::traits::pixel::format_to_string<
			Tag
		>(
			_source
		)
		+
		FCPPT_TEXT(" to ")
		+
		sge::image::traits::pixel::format_to_string<
			Tag
		>(
			_dest
		)
		+
		FCPPT_TEXT('!')
	}
{
}

template<
	typename Tag
>
sge::image::invalid_convert<
	Tag
>::invalid_convert(
	invalid_convert &&
)
noexcept
= default;

template<
	typename Tag
>
sge::image::invalid_convert<
	Tag
>::invalid_convert(
	invalid_convert const &
)
= default;

template<
	typename Tag
>
sge::image::invalid_convert<
	Tag
> &
sge::image::invalid_convert<
	Tag
>::operator=(
	invalid_convert &&
)
noexcept
= default;

template<
	typename Tag
>
sge::image::invalid_convert<
	Tag
> &
sge::image::invalid_convert<
	Tag
>::operator=(
	invalid_convert const &
)
= default;

template<
	typename Tag
>
sge::image::invalid_convert<
	Tag
>::~invalid_convert()
noexcept
= default;

#endif
