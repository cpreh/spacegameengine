//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_LOCK_RECT_FWD_HPP_INCLUDED
#define SGE_RENDERER_LOCK_RECT_FWD_HPP_INCLUDED

#include <sge/renderer/basic_lock_box_fwd.hpp>


namespace sge
{
namespace renderer
{

/**
\brief A typedef for a rect used for locking textures

\ingroup sge_renderer
*/
using
lock_rect
=
sge::renderer::basic_lock_box<
	2
>;

}
}

#endif
