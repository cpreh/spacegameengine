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
#include <sge/image/impl/view/to_static_format.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/store/object.hpp>
#include <sge/image/view/to_wrapped_type.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/runtime_enum.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Tag
>
sge::image::store::object<
	Tag
>::object(
	variant &&_variant
)
:
	variant_{
		std::move(
			_variant
		)
	}
{
}

template<
	typename Tag
>
sge::image::store::object<
	Tag
>::object(
	format const _format,
	dim const &_size,
	fcppt::no_init const &
)
:
	variant_{
		fcppt::runtime_enum<
			sge::image::traits::pixel::format<
				sge::image::traits::image::color_tag<
					Tag
				>
			>
		>(
			_format,
			[
				&_size
			](
				auto const &_static_format
			)
			{
				return
					variant{
						sge::image::store::basic<
							sge::image::impl::view::to_static_format<
								Tag,
								typename
								std::decay<
									decltype(
										_static_format
									)
								>::type
							>
						>(
							_size,
							fcppt::no_init{}
						)
					};
			}
		)
	}
{
}

template<
	typename Tag
>
sge::image::store::object<
	Tag
>::object(
	object &&
) = default;

template<
	typename Tag
>
sge::image::store::object<
	Tag
> &
sge::image::store::object<
	Tag
>::operator=(
	object &&
) = default;

template<
	typename Tag
>
sge::image::store::object<
	Tag
>::~object()
{
}

template<
	typename Tag
>
typename
sge::image::store::object<
	Tag
>::variant &
sge::image::store::object<
	Tag
>::get()
{
	return
		variant_;
}

template<
	typename Tag
>
typename
sge::image::store::object<
	Tag
>::variant const &
sge::image::store::object<
	Tag
>::get() const
{
	return
		variant_;
}

#endif
