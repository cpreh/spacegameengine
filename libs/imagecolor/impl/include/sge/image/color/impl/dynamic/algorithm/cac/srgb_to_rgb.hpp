//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_SRGB_TO_RGB_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_SRGB_TO_RGB_HPP_INCLUDED

#include <mizuiro/color/space/rgb.hpp>
#include <mizuiro/color/space/srgb.hpp>
#include <mizuiro/color/types/space.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::image::color::impl::dynamic::algorithm::cac
{

// TODO(philipp): Simplify this?
template <typename SourceFormat, typename DestFormat>
using srgb_to_rgb = std::conjunction<
    std::is_same<
        mizuiro::color::types::space<typename DestFormat::color_format>,
        mizuiro::color::space::srgb>,
    std::is_same<
        mizuiro::color::types::space<typename SourceFormat::color_format>,
        mizuiro::color::space::rgb>>;

}

#endif
