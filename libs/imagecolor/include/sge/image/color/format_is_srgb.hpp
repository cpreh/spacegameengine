//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_FORMAT_IS_SRGB_HPP_INCLUDED
#define SGE_IMAGE_COLOR_FORMAT_IS_SRGB_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/detail/symbol.hpp>


namespace sge::image::color
{

SGE_IMAGE_COLOR_DETAIL_SYMBOL
bool
format_is_srgb(
	sge::image::color::format
);

}

#endif
