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


#ifndef SGE_SRC_IMAGE_VIEW_SUB_OUT_OF_RANGE_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_VIEW_SUB_OUT_OF_RANGE_IMPL_HPP_INCLUDED

#include <sge/image/view/sub_out_of_range.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/box/output.hpp>


template<
	typename Box
>
sge::image::view::sub_out_of_range<Box>::sub_out_of_range(
	Box const &_outer,
	Box const &_inner
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
	outer_(_outer),
	inner_(_inner)
{
}

template<
	typename Box
>
Box const &
sge::image::view::sub_out_of_range<Box>::outer() const
{
	return outer_;
}

template<
	typename Box
>
Box const &
sge::image::view::sub_out_of_range<Box>::inner() const
{
	return inner_;
}

template<
	typename Box
>
sge::image::view::sub_out_of_range<Box>::~sub_out_of_range() throw()
{
}

#endif
