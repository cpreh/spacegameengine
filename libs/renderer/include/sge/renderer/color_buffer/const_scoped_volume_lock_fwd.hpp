//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_COLOR_BUFFER_CONST_SCOPED_VOLUME_LOCK_FWD_HPP_INCLUDED
#define SGE_RENDERER_COLOR_BUFFER_CONST_SCOPED_VOLUME_LOCK_FWD_HPP_INCLUDED

#include <sge/image3d/tag.hpp>
#include <sge/renderer/buffer/const_scoped_lock_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace color_buffer
{

/**
\brief A const scoped lock for volumes

\ingroup sge_renderer
*/
typedef
sge::renderer::buffer::const_scoped_lock<
	sge::image3d::tag
>
const_scoped_volume_lock;

}
}
}

#endif
