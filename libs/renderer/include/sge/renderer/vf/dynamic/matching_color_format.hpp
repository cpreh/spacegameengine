//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DYNAMIC_MATCHING_COLOR_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_MATCHING_COLOR_FORMAT_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>

namespace sge::renderer::vf::dynamic
{

SGE_RENDERER_DETAIL_SYMBOL
sge::image::color::format matching_color_format(
    sge::image::color::format, sge::renderer::vf::dynamic::color_format_vector const &);

}

#endif
