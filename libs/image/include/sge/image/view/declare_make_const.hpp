//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_VIEW_DECLARE_MAKE_CONST_HPP_INCLUDED
#define SGE_IMAGE_VIEW_DECLARE_MAKE_CONST_HPP_INCLUDED

#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/dim_fwd.hpp>
#include <sge/image/pitch_fwd.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/make_const.hpp>


#define SGE_IMAGE_VIEW_DECLARE_MAKE_CONST(\
	tag\
)\
extern \
template \
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL \
sge::image::view::const_object< \
	tag \
> \
sge::image::view::make_const( \
	sge::image::const_raw_pointer, \
	sge::image::dim< \
		tag \
	> const &, \
	sge::image::traits::pixel::format< \
		sge::image::traits::image::color_tag< \
			tag \
		> \
	>, \
	sge::image::pitch< \
		tag \
	> const & \
)

#endif
