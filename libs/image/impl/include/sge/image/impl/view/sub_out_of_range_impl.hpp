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


#ifndef SGE_IMAGE_IMPL_VIEW_SUB_OUT_OF_RANGE_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_SUB_OUT_OF_RANGE_IMPL_HPP_INCLUDED

#include <sge/image/box.hpp>
#include <sge/image/view/sub_out_of_range.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/box/output.hpp>


template<
	typename Tag
>
sge::image::view::sub_out_of_range<
	Tag
>::sub_out_of_range(
	box const &_outer,
	box const &_inner
)
:
	sge::image::exception(
		(
			fcppt::format(
				FCPPT_TEXT("sub_out_of_range: %1% not in %2%!")
			)
			% _inner
			% _outer
		).str()
	),
	outer_(
		_outer
	),
	inner_(
		_inner
	)
{
}

template<
	typename Tag
>
sge::image::view::sub_out_of_range<
	Tag
>::sub_out_of_range(
	sub_out_of_range &&
)
= default;

template<
	typename Tag
>
sge::image::view::sub_out_of_range<
	Tag
>::sub_out_of_range(
	sub_out_of_range const &
)
= default;

template<
	typename Tag
>
sge::image::view::sub_out_of_range<
	Tag
> &
sge::image::view::sub_out_of_range<
	Tag
>::operator=(
	sub_out_of_range &&
)
= default;

template<
	typename Tag
>
sge::image::view::sub_out_of_range<
	Tag
> &
sge::image::view::sub_out_of_range<
	Tag
>::operator=(
	sub_out_of_range const &
)
= default;

template<
	typename Tag
>
typename
sge::image::view::sub_out_of_range<
	Tag
>::box const &
sge::image::view::sub_out_of_range<
	Tag
>::outer() const
{
	return
		outer_;
}

template<
	typename Tag
>
typename
sge::image::view::sub_out_of_range<
	Tag
>::box const &
sge::image::view::sub_out_of_range<
	Tag
>::inner() const
{
	return
		inner_;
}

template<
	typename Tag
>
sge::image::view::sub_out_of_range<
	Tag
>::~sub_out_of_range() noexcept
{
}

#endif
