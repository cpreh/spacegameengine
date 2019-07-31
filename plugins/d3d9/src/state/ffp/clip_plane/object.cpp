//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_clip_plane.hpp>
#include <sge/d3d9/state/ffp/clip_plane/object.hpp>
#include <sge/d3d9/state/ffp/clip_plane/state.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/clip_plane/object.hpp>


sge::d3d9::state::ffp::clip_plane::object::object(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::ffp::clip_plane::state const &_state
)
:
	sge::renderer::state::ffp::clip_plane::object(),
	device_(
		_device
	),
	state_(
		_state
	)
{
}

sge::d3d9::state::ffp::clip_plane::object::~object()
{
}

void
sge::d3d9::state::ffp::clip_plane::object::set(
	sge::renderer::state::index_count const _index
) const
{
	sge::d3d9::devicefuncs::set_clip_plane(
		device_,
		_index,
		state_.area()
	);
}
