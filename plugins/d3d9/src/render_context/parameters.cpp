//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/render_context/parameters.hpp>
#include <sge/d3d9/state/core/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/target/base_fwd.hpp>


sge::d3d9::render_context::parameters::parameters(
	IDirect3DDevice9 &_device,
	sge::renderer::target::base &_target,
	sge::renderer::caps::texture_stages const _texture_stages,
	sge::renderer::caps::light_indices const _light_indices,
	sge::d3d9::state::core::defaults const &_core_defaults,
	sge::d3d9::state::ffp::defaults const &_ffp_defaults
)
:
	device_(
		_device
	),
	target_(
		_target
	),
	texture_stages_(
		_texture_stages
	),
	light_indices_(
		_light_indices
	),
	core_defaults_(
		_core_defaults
	),
	ffp_defaults_(
		_ffp_defaults
	)
{
}

IDirect3DDevice9 &
sge::d3d9::render_context::parameters::device() const
{
	return
		device_.get();
}

sge::renderer::target::base &
sge::d3d9::render_context::parameters::target() const
{
	return
		target_.get();
}

sge::renderer::caps::texture_stages const
sge::d3d9::render_context::parameters::texture_stages() const
{
	return
		texture_stages_;
}

sge::renderer::caps::light_indices const
sge::d3d9::render_context::parameters::light_indices() const
{
	return
		light_indices_;
}

sge::d3d9::state::core::defaults const &
sge::d3d9::render_context::parameters::core_defaults() const
{
	return
		core_defaults_.get();
}

sge::d3d9::state::ffp::defaults const &
sge::d3d9::render_context::parameters::ffp_defaults() const
{
	return
		ffp_defaults_.get();
}
