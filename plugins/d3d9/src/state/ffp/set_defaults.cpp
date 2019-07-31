//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/defaults.hpp>
#include <sge/d3d9/state/ffp/set_defaults.hpp>
#include <sge/d3d9/state/ffp/alpha_test/object.hpp>
#include <sge/d3d9/state/ffp/clip_plane/set.hpp>
#include <sge/d3d9/state/ffp/fog/object.hpp>
#include <sge/d3d9/state/ffp/lighting/object.hpp>
#include <sge/d3d9/state/ffp/lighting/light/set.hpp>
#include <sge/d3d9/state/ffp/lighting/material/object.hpp>
#include <sge/d3d9/state/ffp/misc/object.hpp>
#include <sge/d3d9/state/ffp/sampler/set_defaults.hpp>
#include <sge/d3d9/state/ffp/transform/set_defaults.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>


void
sge::d3d9::state::ffp::set_defaults(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::ffp::defaults const &_defaults,
	sge::renderer::caps::light_indices const _light_indices,
	sge::renderer::caps::texture_stages const _texture_stages
)
{
	_defaults.alpha_test().set();

	sge::d3d9::state::ffp::clip_plane::set(
		_device,
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector()
	);

	_defaults.fog().set();

	_defaults.lighting().set();

	sge::d3d9::state::ffp::lighting::light::set(
		_device,
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector(),
		_light_indices
	);

	_defaults.material().set();

	_defaults.misc().set();

	sge::d3d9::state::ffp::sampler::set_defaults(
		_device,
		_defaults.sampler(),
		_texture_stages
	);

	sge::d3d9::state::ffp::transform::set_defaults(
		_defaults.transform()
	);
}
