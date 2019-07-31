//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_light.hpp>
#include <sge/d3d9/state/ffp/lighting/light/object.hpp>
#include <sge/d3d9/state/ffp/lighting/light/state.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/lighting/light/object.hpp>


sge::d3d9::state::ffp::lighting::light::object::object(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::ffp::lighting::light::state const &_state
)
:
	sge::renderer::state::ffp::lighting::light::object(),
	device_(
		_device
	),
	state_(
		_state
	)
{
}

sge::d3d9::state::ffp::lighting::light::object::~object()
{
}

void
sge::d3d9::state::ffp::lighting::light::object::set(
	sge::renderer::state::index_count const _index
) const
{
	sge::d3d9::devicefuncs::set_light(
		device_,
		_index,
		state_.light()
	);
}
