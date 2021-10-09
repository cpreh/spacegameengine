//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_TRAITS_PIXEL_STATIC_FORMATS_HPP_INCLUDED
#define SGE_IMAGE_TRAITS_PIXEL_STATIC_FORMATS_HPP_INCLUDED

#include <sge/image/traits/pixel/static_formats_tpl_fwd.hpp>

namespace sge::image::traits::pixel
{

template <typename Format>
using static_formats = typename sge::image::traits::pixel::static_formats_tpl<Format>::type;

}

#endif
