//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PIXEL_FORMAT_DEPTH_BITS_HPP_INCLUDED
#define SGE_RENDERER_PIXEL_FORMAT_DEPTH_BITS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/pixel_format/depth_stencil_fwd.hpp>
#include <sge/renderer/pixel_format/optional_bit_count_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace pixel_format
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::pixel_format::optional_bit_count
depth_bits(
	sge::renderer::pixel_format::depth_stencil
);

}
}
}

#endif
