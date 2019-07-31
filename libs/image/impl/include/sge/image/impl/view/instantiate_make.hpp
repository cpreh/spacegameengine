//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/dim_fwd.hpp>
#include <sge/image/pitch_fwd.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/impl/view/make_impl.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/view/object.hpp>


#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE(\
	tag\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
sge::image::view::object<\
	tag\
> \
sge::image::view::make< \
	tag \
>( \
	sge::image::raw_pointer, \
	sge::image::dim<\
		tag\
	> const &,\
	sge::image::traits::pixel::format<\
		sge::image::traits::image::color_tag<\
			tag\
		> \
	> ,\
	sge::image::pitch<\
		tag\
	> const &\
)

#endif
