//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_COLOR_BUFFER_WRITABLE_VOLUME_FWD_HPP_INCLUDED
#define SGE_RENDERER_COLOR_BUFFER_WRITABLE_VOLUME_FWD_HPP_INCLUDED

#include <sge/renderer/buffer/writable_fwd.hpp>
#include <sge/renderer/color_buffer/tag_from_dimension.hpp>


namespace sge
{
namespace renderer
{
namespace color_buffer
{

/**
\brief A three-dimensional color buffer that can be written

\ingroup sge_renderer
*/
using
writable_volume
=
sge::renderer::buffer::writable<
	sge::renderer::color_buffer::tag_from_dimension<
		3U
	>
>;

}
}
}

#endif
