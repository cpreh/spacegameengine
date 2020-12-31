//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/clip_plane/area.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters.hpp>


sge::renderer::state::ffp::clip_plane::parameters::parameters(
	sge::renderer::state::ffp::clip_plane::area const _area
)
:
	area_(
		_area
	)
{
}

sge::renderer::state::ffp::clip_plane::area const &
sge::renderer::state::ffp::clip_plane::parameters::area() const
{
	return
		area_;
}
