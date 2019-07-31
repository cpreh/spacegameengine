//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_TRAITS_PIXEL_FORMAT_STRIDE_HPP_INCLUDED
#define SGE_IMAGE_TRAITS_PIXEL_FORMAT_STRIDE_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/traits/pixel/format_stride_tpl_fwd.hpp>


namespace sge
{
namespace image
{
namespace traits
{
namespace pixel
{

template<
	typename Tag
>
inline
sge::image::size_type
format_stride(
	sge::image::traits::pixel::format<
		Tag
	> const _format
)
{
	return
		sge::image::traits::pixel::format_stride_tpl<
			Tag
		>::execute(
			_format
		);
}

}
}
}
}

#endif
