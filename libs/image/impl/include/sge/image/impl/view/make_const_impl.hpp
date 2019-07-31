//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_MAKE_CONST_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_MAKE_CONST_IMPL_HPP_INCLUDED

#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/dim_fwd.hpp>
#include <sge/image/pitch_fwd.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/image/view/to_const.hpp>


template<
	typename Tag
>
sge::image::view::const_object<
	Tag
>
sge::image::view::make_const(
	sge::image::const_raw_pointer const _data,
	sge::image::dim<
		Tag
	> const &_dim,
	sge::image::traits::pixel::format<
		sge::image::traits::image::color_tag<
			Tag
		>
	> const _format,
	sge::image::pitch<
		Tag
	> const &_pitch
)
{
	return
		sge::image::view::to_const<
			Tag
		>(
			sge::image::view::make<
				Tag
			>(
				const_cast<
					sge::image::raw_pointer
				>(
					_data
				),
				_dim,
				_format,
				_pitch
			)
		);
}

#endif
