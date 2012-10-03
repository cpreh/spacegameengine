/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/clear.hpp>
#include <sge/d3d9/devicefuncs/draw_indexed_primitive.hpp>
#include <sge/d3d9/devicefuncs/draw_primitive.hpp>
#include <sge/d3d9/devicefuncs/set_index_buffer.hpp>
#include <sge/d3d9/devicefuncs/set_stream_source.hpp>
#include <sge/d3d9/devicefuncs/set_vertex_declaration.hpp>
#include <sge/d3d9/render_context/object.hpp>
#include <sge/d3d9/state/core/defaults.hpp>
#include <sge/d3d9/state/core/set_defaults.hpp>
#include <sge/d3d9/state/core/blend/set.hpp>
#include <sge/d3d9/state/core/depth_stencil/set.hpp>
#include <sge/d3d9/state/core/rasterizer/set.hpp>
#include <sge/d3d9/state/core/sampler/set.hpp>
#include <sge/d3d9/state/ffp/defaults.hpp>
#include <sge/d3d9/state/ffp/set_defaults.hpp>
#include <sge/d3d9/state/ffp/alpha_test/set.hpp>
#include <sge/d3d9/state/ffp/clip_plane/set.hpp>
#include <sge/d3d9/state/ffp/fog/set.hpp>
#include <sge/d3d9/target/base.hpp>
#include <sge/d3d9/texture/set.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/const_optional_vertex_declaration_ref.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/optional_offscreen_ref.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/dynamic_optional_cast.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/pre.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/d3d9/cg/program/activate.hpp>
#include <sge/d3d9/cg/program/deactivate.hpp>
#include <sge/d3d9/cg/texture/activate.hpp>
#include <sge/d3d9/cg/texture/deactivate.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#endif


sge::d3d9::render_context::object::object(
	IDirect3DDevice9 &_device,
	sge::renderer::target::base &_target,
	sge::renderer::caps::texture_stages const _texture_stages,
	sge::d3d9::state::core::defaults const &_core_defaults,
	sge::d3d9::state::ffp::defaults const &_ffp_defaults
)
:
	sge::renderer::context::ffp(),
	device_(
		_device
	),
	target_(
		_target
	),
	scoped_target_(
		dynamic_cast<
			sge::d3d9::target::base &
		>(
			target_
		)
	),
	offscreen_target_(),
	core_defaults_(
		_core_defaults
	),
	ffp_defaults_(
		_ffp_defaults
	)
#if defined(SGE_RENDERER_HAVE_CG)
	,
	scoped_cg_device_(
		device_
	)
#endif
{
	sge::d3d9::state::core::set_defaults(
		core_defaults_,
		_texture_stages
	);

	sge::d3d9::state::ffp::set_defaults(
		ffp_defaults_
	);
}

sge::d3d9::render_context::object::~object()
{
}

bool
sge::d3d9::render_context::object::needs_present() const
{
	return
		scoped_target_.target().needs_present();
}

sge::renderer::target::base &
sge::d3d9::render_context::object::target()
{
	return
		target_;
}

void
sge::d3d9::render_context::object::clear(
	sge::renderer::clear::parameters const &_parameters
)
{
	sge::d3d9::devicefuncs::clear(
		device_,
		_parameters
	);
}

void
sge::d3d9::render_context::object::offscreen_target(
	sge::renderer::target::optional_offscreen_ref const &_new_target
)
{
	if(
		_new_target
	)
	{
		FCPPT_ASSERT_PRE(
			!offscreen_target_
		);

		scoped_target_.target().active(
			false
		);

		offscreen_target_ =
			fcppt::dynamic_optional_cast<
				sge::d3d9::target::base
			>(
				_new_target
			);

		offscreen_target_->active(
			true
		);
	}
	else
	{
		FCPPT_ASSERT_PRE(
			offscreen_target_
		);

		offscreen_target_->active(
			false
		);

		offscreen_target_ =
			sge::d3d9::render_context::object::optional_target_base_ref();

		scoped_target_.target().active(
			true
		);
	}
}

void
sge::d3d9::render_context::object::render_indexed(
	sge::renderer::index_buffer const &_index_buffer,
	sge::renderer::first_vertex const _first_vertex,
	sge::renderer::vertex_count const _num_vertices,
	sge::renderer::primitive_type::type const _primitive_type,
	sge::renderer::first_index const _first_index,
	sge::renderer::index_count const _num_indices
)
{
	sge::d3d9::devicefuncs::set_index_buffer(
		device_,
		_index_buffer
	);

	sge::d3d9::devicefuncs::draw_indexed_primitive(
		device_,
		_first_vertex,
		_num_vertices,
		_primitive_type,
		_first_index,
		_num_indices
	);
}

void
sge::d3d9::render_context::object::render_nonindexed(
	sge::renderer::first_vertex const _first_vertex,
	sge::renderer::vertex_count const _num_vertices,
	sge::renderer::primitive_type::type const _primitive_type
)
{
	sge::d3d9::devicefuncs::draw_primitive(
		device_,
		_first_vertex,
		_num_vertices,
		_primitive_type
	);
}

void
sge::d3d9::render_context::object::activate_vertex_buffer(
	sge::renderer::vertex_buffer const &_buffer
)
{
	sge::d3d9::devicefuncs::set_stream_source(
		device_,
		_buffer
	);
}

void
sge::d3d9::render_context::object::deactivate_vertex_buffer(
	sge::renderer::vertex_buffer const &_buffer
)
{
}

void
sge::d3d9::render_context::object::vertex_declaration(
	sge::renderer::const_optional_vertex_declaration_ref const &_declaration
)
{
	if(
		!_declaration
	)
		return;

	sge::d3d9::devicefuncs::set_vertex_declaration(
		device_,
		*_declaration
	);
}

void
sge::d3d9::render_context::object::texture(
	sge::renderer::texture::const_optional_base_ref const &_texture,
	sge::renderer::texture::stage const _stage
)
{
	sge::d3d9::texture::set(
		device_,
		_stage,
		_texture
	);
}

void
sge::d3d9::render_context::object::blend_state(
	sge::renderer::state::core::blend::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::core::blend::set(
		_state,
		core_defaults_.blend()
	);
}

void
sge::d3d9::render_context::object::depth_stencil_state(
	sge::renderer::state::core::depth_stencil::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::core::depth_stencil::set(
		_state,
		core_defaults_.depth_stencil()
	);
}

void
sge::d3d9::render_context::object::rasterizer_state(
	sge::renderer::state::core::rasterizer::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::core::rasterizer::set(
		_state,
		core_defaults_.rasterizer()
	);
}

void
sge::d3d9::render_context::object::sampler_state(
	sge::renderer::state::core::sampler::const_optional_object_ref_map const &_states
)
{
	sge::d3d9::state::core::sampler::set(
		_states,
		core_defaults_.sampler()
	);
}

#if defined(SGE_RENDERER_HAVE_CG)
void
sge::d3d9::render_context::object::set_cg_program(
	sge::renderer::cg::loaded_program const &_program
)
{
	sge::d3d9::cg::program::activate(
		_program
	);
}

void
sge::d3d9::render_context::object::unset_cg_program(
	sge::renderer::cg::loaded_program const &_program
)
{
	sge::d3d9::cg::program::deactivate(
		_program
	);
}

sge::renderer::texture::stage const
sge::d3d9::render_context::object::set_cg_texture(
	sge::renderer::cg::loaded_texture const &_texture
)
{
	return
		sge::d3d9::cg::texture::activate(
			_texture
		);
}

void
sge::d3d9::render_context::object::unset_cg_texture(
	sge::renderer::cg::loaded_texture const &_texture
)
{
	sge::d3d9::cg::texture::deactivate(
		_texture
	);
}
#endif

void
sge::d3d9::render_context::object::alpha_test_state(
	sge::renderer::state::ffp::alpha_test::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::ffp::alpha_test::set(
		_state,
		ffp_defaults_.alpha_test()
	);
}

void
sge::d3d9::render_context::object::clip_plane_state(
	sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &_states
)
{
	sge::d3d9::state::ffp::clip_plane::set(
		device_,
		_states
	);
}

void
sge::d3d9::render_context::object::fog_state(
	sge::renderer::state::ffp::fog::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::ffp::fog::set(
		_state,
		ffp_defaults_.fog()
	);
}

void
sge::d3d9::render_context::object::lighting_state(
	sge::renderer::state::ffp::lighting::const_optional_object_ref const &_state
)
{
}

void
sge::d3d9::render_context::object::lights_state(
	sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &_states
)
{
}

void
sge::d3d9::render_context::object::material_state(
	sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &_state
)
{
}

void
sge::d3d9::render_context::object::misc_state(
	sge::renderer::state::ffp::misc::const_optional_object_ref const &_state
)
{
}

void
sge::d3d9::render_context::object::sampler_ffp_state(
	sge::renderer::state::ffp::sampler::const_object_ref_vector const &_states
)
{
}

void
sge::d3d9::render_context::object::transform(
	sge::renderer::state::ffp::transform::mode::type const _mode,
	sge::renderer::state::ffp::transform::const_optional_object_ref const &_state
)
{
}
