//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_PIXEL_CONVERT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_PIXEL_CONVERT_IMPL_HPP_INCLUDED

#include <sge/image/enable_if_has_format.hpp>
#include <sge/image/impl/traits/static_converter.hpp>
#include <sge/image/pixel/convert.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/image/pixel/object.hpp>
#include <mizuiro/color/convert.hpp>
#include <fcppt/variant/apply.hpp>


template<
	typename Tag,
	typename Format
>
sge::image::enable_if_has_format<
	Tag,
	Format,
	sge::image::pixel::mizuiro_type<
		Format
	>
>
sge::image::pixel::convert(
	sge::image::pixel::object<
		Tag
	> const &_pixel
)
{
	return
		fcppt::variant::apply(
			[](
				auto const &_source
			)
			{
				return
					mizuiro::color::convert<
						sge::image::impl::traits::static_converter<
							Tag
						>,
						Format
					>(
						_source
					);
			},
			_pixel.get()
		);
}

#endif
