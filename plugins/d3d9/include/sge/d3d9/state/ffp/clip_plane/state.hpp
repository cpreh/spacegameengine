//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_FFP_CLIP_PLANE_STATE_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_CLIP_PLANE_STATE_HPP_INCLUDED

#include <sge/d3d9/state/ffp/clip_plane/state_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/area.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace clip_plane
{

class state
{
public:
	explicit
	state(
		sge::renderer::state::ffp::clip_plane::area const &
	);

	sge::renderer::state::ffp::clip_plane::area const &
	area() const;
private:
	sge::renderer::state::ffp::clip_plane::area area_;
};

}
}
}
}
}

#endif
