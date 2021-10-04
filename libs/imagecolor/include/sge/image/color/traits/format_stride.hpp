//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_TRAITS_FORMAT_STRIDE_HPP_INCLUDED
#define SGE_IMAGE_COLOR_TRAITS_FORMAT_STRIDE_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/detail/symbol.hpp>
#include <sge/image/traits/pixel/format_stride_tpl_fwd.hpp>


namespace sge::image::traits::pixel
{

template<>
struct format_stride_tpl<
	sge::image::color::tag
>
{
	SGE_IMAGE_COLOR_DETAIL_SYMBOL
	static
	sge::image::size_type
	execute(
		sge::image::color::format
	);
};

}

#endif
