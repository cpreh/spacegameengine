//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/tag.hpp>
#include <sge/renderer/color_buffer/scoped_surface_lock.hpp>
#include <sge/renderer/color_buffer/writable_surface.hpp>
#include <sge/renderer/impl/buffer/instantiate_scoped_lock.hpp>


SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_SCOPED_LOCK(
	sge::image2d::tag
);
