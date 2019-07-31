//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PIXEL_FORMAT_COLOR_BITS_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_FORMAT_COLOR_BITS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/color_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace pixel_format
{

/**
\brief Calculates how many bits are needed for one pixel

Calculates how many bits are needed for a pixel from \a color

\param color The color format to calculate the size from
*/
SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::pixel_format::bit_count
color_bits(
	sge::renderer::pixel_format::color color
);

}
}
}

#endif
