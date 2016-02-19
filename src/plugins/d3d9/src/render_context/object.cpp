/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/d3d9/devicefuncs/clear.hpp>
#include <sge/d3d9/devicefuncs/draw_indexed_primitive.hpp>
#include <sge/d3d9/devicefuncs/draw_primitive.hpp>
#include <sge/d3d9/devicefuncs/set_index_buffer.hpp>
#include <sge/d3d9/devicefuncs/set_stream_source.hpp>
#include <sge/d3d9/devicefuncs/set_vertex_declaration.hpp>
#include <sge/d3d9/render_context/object.hpp>
#include <sge/d3d9/render_context/parameters.hpp>
#include <sge/d3d9/state/set_defaults.hpp>
#include <sge/d3d9/state/core/defaults.hpp>
#include <sge/d3d9/state/core/blend/set.hpp>
#include <sge/d3d9/state/core/depth_stencil/set.hpp>
#include <sge/d3d9/state/core/rasterizer/set.hpp>
#include <sge/d3d9/state/core/sampler/set.hpp>
#include <sge/d3d9/state/ffp/defaults.hpp>
#include <sge/d3d9/state/ffp/alpha_test/set.hpp>
#include <sge/d3d9/state/ffp/clip_plane/set.hpp>
#include <sge/d3d9/state/ffp/fog/set.hpp>
#include <sge/d3d9/state/ffp/lighting/set.hpp>
#include <sge/d3d9/state/ffp/lighting/light/set.hpp>
#include <sge/d3d9/state/ffp/lighting/material/set.hpp>
#include <sge/d3d9/state/ffp/misc/set.hpp>
#include <sge/d3d9/state/ffp/sampler/set.hpp>
#include <sge/d3d9/state/ffp/transform/set.hpp>
#include <sge/d3d9/target/base.hpp>
#include <sge/d3d9/texture/set.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
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
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/assert/optional_error.hpp>
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
	sge::d3d9::render_context::parameters const &_parameters
)
:
	sge::renderer::context::ffp(),
	parameters_(
		_parameters
	),
	scoped_target_(
		dynamic_cast<
			sge::d3d9::target::base &
		>(
			parameters_.target()
		)
	),
	offscreen_target_()
#if defined(SGE_RENDERER_HAVE_CG)
	,
	scoped_cg_device_(
		parameters_.device()
	)
#endif
{
	sge::d3d9::state::set_defaults(
		parameters_.device(),
		parameters_.core_defaults(),
		parameters_.ffp_defaults(),
		parameters_.light_indices(),
		parameters_.texture_stages()
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
		parameters_.target();
}

void
sge::d3d9::render_context::object::clear(
	sge::renderer::clear::parameters const &_parameters
)
{
	sge::d3d9::devicefuncs::clear(
		parameters_.device(),
		_parameters
	);
}

void
sge::d3d9::render_context::object::offscreen_target(
	sge::renderer::target::optional_offscreen_ref const &_new_target
)
{
	fcppt::optional::maybe(
		_new_target,
		[
			this
		]{
			{
				sge::d3d9::target::base &cur_target(
					FCPPT_ASSERT_OPTIONAL_ERROR(
						offscreen_target_
					).get()
				);

				cur_target.active(
					false
				);
			}

			offscreen_target_ =
				sge::d3d9::render_context::object::optional_target_base_ref();

			scoped_target_.target().active(
				true
			);
		},
		[
			this
		](
			fcppt::reference<
				sge::renderer::target::offscreen
			> const _target
		)
		{
			FCPPT_ASSERT_PRE(
				!offscreen_target_.has_value()
			);

			scoped_target_.target().active(
				false
			);

			sge::d3d9::target::base &new_target(
				dynamic_cast<
					sge::d3d9::target::base &
				>(
					_target.get()
				)
			);

			new_target.active(
				true
			);

			offscreen_target_ =
				sge::d3d9::render_context::object::optional_target_base_ref(
					fcppt::make_ref(
						new_target
					)
				);
		}
	);
}

void
sge::d3d9::render_context::object::render_indexed(
	sge::renderer::index::buffer const &_index_buffer,
	sge::renderer::vertex::first const _first_vertex,
	sge::renderer::vertex::count const _num_vertices,
	sge::renderer::primitive_type const _primitive_type,
	sge::renderer::index::first const _first_index,
	sge::renderer::index::count const _num_indices
)
{
	sge::d3d9::devicefuncs::set_index_buffer(
		parameters_.device(),
		_index_buffer
	);

	sge::d3d9::devicefuncs::draw_indexed_primitive(
		parameters_.device(),
		_first_vertex,
		_num_vertices,
		_primitive_type,
		_first_index,
		_num_indices
	);
}

void
sge::d3d9::render_context::object::render_nonindexed(
	sge::renderer::vertex::first const _first_vertex,
	sge::renderer::vertex::count const _num_vertices,
	sge::renderer::primitive_type const _primitive_type
)
{
	sge::d3d9::devicefuncs::draw_primitive(
		parameters_.device(),
		_first_vertex,
		_num_vertices,
		_primitive_type
	);
}

void
sge::d3d9::render_context::object::activate_vertex_buffer(
	sge::renderer::vertex::buffer const &_buffer
)
{
	sge::d3d9::devicefuncs::set_stream_source(
		parameters_.device(),
		_buffer,
		true
	);
}

void
sge::d3d9::render_context::object::deactivate_vertex_buffer(
	sge::renderer::vertex::buffer const &_buffer
)
{
	sge::d3d9::devicefuncs::set_stream_source(
		parameters_.device(),
		_buffer,
		false
	);
}

void
sge::d3d9::render_context::object::vertex_declaration(
	sge::renderer::vertex::const_optional_declaration_ref const &_opt_declaration
)
{
	// TODO: How do we disable a vertex declaration?
	fcppt::optional::maybe_void(
		_opt_declaration,
		[
			this
		](
			fcppt::reference<
				sge::renderer::vertex::declaration const
			> const _declaration
		)
		{
			sge::d3d9::devicefuncs::set_vertex_declaration(
				parameters_.device(),
				_declaration.get()
			);
		}
	);
}

void
sge::d3d9::render_context::object::texture(
	sge::renderer::texture::const_optional_base_ref const &_texture,
	sge::renderer::texture::stage const _stage
)
{
	sge::d3d9::texture::set(
		parameters_.device(),
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
		parameters_.core_defaults().blend()
	);
}

void
sge::d3d9::render_context::object::depth_stencil_state(
	sge::renderer::state::core::depth_stencil::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::core::depth_stencil::set(
		_state,
		parameters_.core_defaults().depth_stencil()
	);
}

void
sge::d3d9::render_context::object::rasterizer_state(
	sge::renderer::state::core::rasterizer::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::core::rasterizer::set(
		_state,
		parameters_.core_defaults().rasterizer()
	);
}

void
sge::d3d9::render_context::object::sampler_state(
	sge::renderer::state::core::sampler::const_optional_object_ref_map const &_states
)
{
	sge::d3d9::state::core::sampler::set(
		_states,
		parameters_.core_defaults().sampler()
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
		parameters_.ffp_defaults().alpha_test()
	);
}

void
sge::d3d9::render_context::object::clip_plane_state(
	sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &_states
)
{
	sge::d3d9::state::ffp::clip_plane::set(
		parameters_.device(),
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
		parameters_.ffp_defaults().fog()
	);
}

void
sge::d3d9::render_context::object::lighting_state(
	sge::renderer::state::ffp::lighting::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::ffp::lighting::set(
		_state,
		parameters_.ffp_defaults().lighting()
	);
}

void
sge::d3d9::render_context::object::lights_state(
	sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &_states
)
{
	sge::d3d9::state::ffp::lighting::light::set(
		parameters_.device(),
		_states,
		parameters_.light_indices()
	);
}

void
sge::d3d9::render_context::object::material_state(
	sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::ffp::lighting::material::set(
		_state,
		parameters_.ffp_defaults().material()
	);
}

void
sge::d3d9::render_context::object::misc_state(
	sge::renderer::state::ffp::misc::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::ffp::misc::set(
		_state,
		parameters_.ffp_defaults().misc()
	);
}

void
sge::d3d9::render_context::object::sampler_ffp_state(
	sge::renderer::state::ffp::sampler::const_object_ref_vector const &_states
)
{
	sge::d3d9::state::ffp::sampler::set(
		parameters_.device(),
		_states,
		parameters_.ffp_defaults().sampler(),
		parameters_.texture_stages()
	);
}

void
sge::d3d9::render_context::object::transform(
	sge::renderer::state::ffp::transform::mode const _mode,
	sge::renderer::state::ffp::transform::const_optional_object_ref const &_state
)
{
	sge::d3d9::state::ffp::transform::set(
		_mode,
		_state,
		parameters_.ffp_defaults().transform()
	);
}
