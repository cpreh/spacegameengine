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


#ifndef SGE_IMAGE_IMPL_ALGORITHM_FILL_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_FILL_IMPL_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/algorithm/fill.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <sge/image/impl/view/format_type.hpp>
#include <sge/image/pixel/convert.hpp>
#include <sge/image/pixel/object_fwd.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <mizuiro/image/algorithm/fill_c.hpp>
#include <fcppt/variant/apply_unary.hpp>


template<
	typename Tag
>
void
sge::image::algorithm::fill(
	sge::image::view::object<
		Tag
	> const &_view,
	sge::image::pixel::object<
		sge::image::traits::image::color_tag<
			Tag
		>
	> const &_value,
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
				sge::image::pixel::convert<
					sge::image::traits::image::color_tag<
						Tag
					>,
					typename
					sge::image::impl::view::format_type<
						decltype(
							_view_inner
						)
					>::color_format
				>(
					_value
				),
				sge::image::impl::algorithm::convert_uninitialized(
					_uninitialized
				)
			);
		},
		_view.get()
	);
}

#endif
