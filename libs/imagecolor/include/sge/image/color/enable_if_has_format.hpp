//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_ENABLE_IF_HAS_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_ENABLE_IF_HAS_FORMAT_HPP_INCLUDED

#include <sge/image/enable_if_has_format.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/traits/static_formats.hpp>

namespace sge::image::color
{

template <typename Format, typename Result>
using enable_if_has_format =
    sge::image::enable_if_has_format<sge::image::color::tag, Format, Result>;

}

#endif
