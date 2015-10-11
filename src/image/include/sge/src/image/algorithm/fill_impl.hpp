/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_IMAGE_ALGORITHM_FILL_IMPL_HPP_INCLUDED
#define SGE_SRC_IMAGE_ALGORITHM_FILL_IMPL_HPP_INCLUDED

#include <sge/image/mizuiro_color.hpp>
#include <sge/image/algorithm/fill.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/traits/any_object_fwd.hpp>
#include <sge/image/traits/color_tag.hpp>
#include <sge/image/traits/view_fwd.hpp>
#include <sge/src/image/algorithm/convert_uninitialized.hpp>
#include <sge/src/image/view/format_type.hpp>
#include <mizuiro/image/algorithm/fill_c.hpp>
#include <fcppt/variant/apply_unary.hpp>


template<
	typename Tag
>
void
sge::image::algorithm::fill(
	typename sge::image::traits::view<
		Tag
	>::type const &_view,
	typename sge::image::traits::any_object<
		typename sge::image::traits::color_tag<
			Tag
		>::type
	>::type const &_value,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	fcppt::variant::apply_unary(
		[
			&_value,
			_uninitialized
		](
			auto const &_view_inner
		)
		{
			mizuiro::image::algorithm::fill_c(
				_view_inner,
				sge::image::color::any::convert<
					typename
					sge::image::view::format_type<
						decltype(
							_view_inner
						)
					>::color_format
				>(
					_value
				),
				sge::image::algorithm::convert_uninitialized(
					_uninitialized
				)
			);
		},
		_view.get()
	);
}

#endif
