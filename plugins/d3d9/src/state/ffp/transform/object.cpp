//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_transform.hpp>
#include <sge/d3d9/state/convert/matrix_mode.hpp>
#include <sge/d3d9/state/ffp/transform/object.hpp>
#include <sge/d3d9/state/ffp/transform/state.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>


sge::d3d9::state::ffp::transform::object::object(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::ffp::transform::state const &_state
)
:
	device_(
		_device
	),
	state_(
		_state
	)
{
}

sge::d3d9::state::ffp::transform::object::~object()
{
}

void
sge::d3d9::state::ffp::transform::object::set(
	sge::renderer::state::ffp::transform::mode const _mode
) const
{
	sge::d3d9::devicefuncs::set_transform(
		device_,
		sge::d3d9::state::convert::matrix_mode(
			_mode
		),
		state_.matrix()
	);
}
