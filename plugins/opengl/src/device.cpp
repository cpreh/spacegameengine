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


#include <sge/opengl/device.hpp>
#include <sge/opengl/get_device_caps.hpp>
#include <sge/opengl/init_multi_sampling.hpp>
#include <sge/opengl/init_srgb.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/fbo/create_depth_stencil_surface.hpp>
#include <sge/opengl/fbo/create_target.hpp>
#include <sge/opengl/occlusion_query/create.hpp>
#include <sge/opengl/index/create_buffer.hpp>
#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/render_context/create.hpp>
#include <sge/opengl/render_context/end.hpp>
#include <sge/opengl/state/core/blend/create.hpp>
#include <sge/opengl/state/core/depth_stencil/create.hpp>
#include <sge/opengl/state/core/rasterizer/create.hpp>
#include <sge/opengl/state/core/sampler/create.hpp>
#include <sge/opengl/state/ffp/alpha_test/create.hpp>
#include <sge/opengl/state/ffp/clip_plane/create.hpp>
#include <sge/opengl/state/ffp/fog/create.hpp>
#include <sge/opengl/state/ffp/lighting/create.hpp>
#include <sge/opengl/state/ffp/lighting/light/create.hpp>
#include <sge/opengl/state/ffp/lighting/material/create.hpp>
#include <sge/opengl/state/ffp/misc/create.hpp>
#include <sge/opengl/state/ffp/sampler/create.hpp>
#include <sge/opengl/state/ffp/transform/create.hpp>
#include <sge/opengl/target/create_onscreen.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/create_cube.hpp>
#include <sge/opengl/texture/create_depth_stencil.hpp>
#include <sge/opengl/texture/create_planar.hpp>
#include <sge/opengl/texture/create_volume.hpp>
#include <sge/opengl/vertex/create_buffer.hpp>
#include <sge/opengl/vertex/create_declaration.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/parameters_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/alpha_test/object.hpp>
#include <sge/renderer/state/ffp/alpha_test/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/alpha_test/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/object.hpp>
#include <sge/renderer/state/ffp/clip_plane/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/fog/object.hpp>
#include <sge/renderer/state/ffp/fog/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/fog/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/object.hpp>
#include <sge/renderer/state/ffp/lighting/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/object.hpp>
#include <sge/renderer/state/ffp/lighting/light/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/object.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/misc/object.hpp>
#include <sge/renderer/state/ffp/misc/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/misc/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/object.hpp>
#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_unique_ptr.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <awl/visual/object.hpp>
#include <awl/window/object.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/cast/dynamic_cross.hpp>
#include <fcppt/log/object_fwd.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/opengl/cg/profile/create.hpp>
#include <sge/opengl/cg/program/load.hpp>
#include <sge/opengl/cg/program/optimal_options.hpp>
#include <sge/opengl/cg/program/transform_vertex.hpp>
#include <sge/opengl/cg/texture/load.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#endif


sge::opengl::device::device(
	fcppt::log::object &_log,
	sge::renderer::display_mode::parameters const &_display_mode,
	awl::window::object &_window,
	sge::opengl::platform::system &_platform_system,
	sge::opengl::backend::system &_backend_system
)
:
	log_{
		_log
	},
	device_state_(
		_platform_system.create_device_state(
			_display_mode.display_mode(),
			_window
		)
	),
	backend_context_(
		_backend_system.create_context(
			_window
		)
	),
	scoped_current_(
		*backend_context_
	),
	info_(
		_log,
		scoped_current_.get()
	),
	context_(
		info_
	),
	caps_(
		sge::opengl::get_device_caps(
			context_
		)
	),
	onscreen_target_(
		sge::opengl::target::create_onscreen(
			context_,
			scoped_current_.get(),
			_window
		)
	)
{
	scoped_current_.get().vsync(
		_display_mode.vsync()
	);

	fcppt::optional::maybe_void(
		fcppt::cast::dynamic_cross<
			sge::renderer::visual_base const
		>(
			_window.visual()
		),
		[
			&_log,
			this
		](
			fcppt::reference<
				sge::renderer::visual_base const
			> const _visual
		)
		{
			sge::opengl::init_multi_sampling(
				context_,
				_visual.get().pixel_format().multi_samples()
			);

			sge::opengl::init_srgb(
				_log,
				context_,
				_visual.get().pixel_format().srgb()
			);
		}
	);
}

sge::opengl::device::~device()
{
}

sge::renderer::context::core_unique_ptr
sge::opengl::device::begin_rendering(
	sge::renderer::target::base &_target
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::context::core
		>(
			this->begin_rendering_ffp(
				_target
			)
		);
}

void
sge::opengl::device::end_rendering(
	sge::renderer::context::core &_context
)
{
	sge::opengl::render_context::end(
		_context
	);
}

sge::renderer::target::offscreen_unique_ptr
sge::opengl::device::create_target()
{
	return
		sge::opengl::fbo::create_target(
			context_
		);
}

sge::renderer::texture::planar_unique_ptr
sge::opengl::device::create_planar_texture(
	sge::renderer::texture::planar_parameters const &_parameters
)
{
	return
		sge::opengl::texture::create_planar(
			this->texture_parameters(),
			_parameters
		);
}

sge::renderer::texture::depth_stencil_unique_ptr
sge::opengl::device::create_depth_stencil_texture(
	sge::renderer::texture::depth_stencil_parameters const &_parameters
)
{
	return
		sge::opengl::texture::create_depth_stencil(
			this->texture_parameters(),
			_parameters
		);
}

sge::renderer::depth_stencil_buffer::surface_unique_ptr
sge::opengl::device::create_depth_stencil_surface(
	sge::renderer::depth_stencil_buffer::surface_parameters const &_parameters
)
{
	return
		sge::renderer::depth_stencil_buffer::surface_unique_ptr(
			sge::opengl::fbo::create_depth_stencil_surface(
				context_,
				_parameters
			)
		);
}

sge::renderer::texture::volume_unique_ptr
sge::opengl::device::create_volume_texture(
	sge::renderer::texture::volume_parameters const &_parameters
)
{
	return
		sge::opengl::texture::create_volume(
			this->texture_parameters(),
			_parameters
		);
}

sge::renderer::texture::cube_unique_ptr
sge::opengl::device::create_cube_texture(
	sge::renderer::texture::cube_parameters const &_parameters
)
{
	return
		sge::opengl::texture::create_cube(
			this->texture_parameters(),
			_parameters
		);
}

sge::renderer::vertex::declaration_unique_ptr
sge::opengl::device::create_vertex_declaration(
	sge::renderer::vertex::declaration_parameters const &_parameters
)
{
	return
		sge::opengl::vertex::create_declaration(
			log_,
			context_,
			_parameters
		);
}

sge::renderer::vertex::buffer_unique_ptr
sge::opengl::device::create_vertex_buffer(
	sge::renderer::vertex::buffer_parameters const &_parameters
)
{
	return
		sge::opengl::vertex::create_buffer(
			context_,
			_parameters
		);
}

sge::renderer::index::buffer_unique_ptr
sge::opengl::device::create_index_buffer(
	sge::renderer::index::buffer_parameters const &_parameters
)
{
	return
		sge::opengl::index::create_buffer(
			context_,
			_parameters
		);
}

sge::renderer::occlusion_query::object_unique_ptr
sge::opengl::device::create_occlusion_query()
{
	return
		sge::opengl::occlusion_query::create(
			context_
		);
}

sge::renderer::state::core::blend::object_unique_ptr
sge::opengl::device::create_blend_state(
	sge::renderer::state::core::blend::parameters const &_parameters
)
{
	return
		sge::opengl::state::core::blend::create(
			context_,
			_parameters
		);
}

sge::renderer::state::core::depth_stencil::object_unique_ptr
sge::opengl::device::create_depth_stencil_state(
	sge::renderer::state::core::depth_stencil::parameters const &_parameters
)
{
	return
		sge::opengl::state::core::depth_stencil::create(
			context_,
			_parameters
		);
}

sge::renderer::state::core::rasterizer::object_unique_ptr
sge::opengl::device::create_rasterizer_state(
	sge::renderer::state::core::rasterizer::parameters const &_parameters
)
{
	return
		sge::opengl::state::core::rasterizer::create(
			_parameters
		);
}

sge::renderer::state::core::sampler::object_unique_ptr
sge::opengl::device::create_sampler_state(
	sge::renderer::state::core::sampler::parameters const &_parameters
)
{
	return
		sge::opengl::state::core::sampler::create(
			context_,
			_parameters
		);
}

#if defined(SGE_RENDERER_HAVE_CG)
sge::cg::profile::object
sge::opengl::device::create_cg_profile(
	sge::cg::profile::shader_type const _shader_type
)
{
	return
		sge::opengl::cg::profile::create(
			_shader_type
		);
}

sge::cg::program::compile_options
sge::opengl::device::cg_compile_options(
	sge::cg::context::object const &_context,
	sge::cg::profile::object const &_profile
)
{
	return
		sge::opengl::cg::program::optimal_options(
			_context,
			_profile
		);
}

sge::renderer::cg::loaded_program_unique_ptr
sge::opengl::device::load_cg_program(
	sge::cg::program::object &_program
)
{
	return
		sge::opengl::cg::program::load(
			_program
		);
}

sge::renderer::cg::loaded_texture_unique_ptr
sge::opengl::device::load_cg_texture(
	sge::cg::parameter::object const &_parameter,
	sge::renderer::texture::base &_texture
)
{
	return
		sge::opengl::cg::texture::load(
			log_,
			context_,
			_parameter,
			_texture
		);
}

sge::cg::program::source
sge::opengl::device::transform_cg_vertex_program(
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::cg::program::source const &_source
)
{
	return
		sge::opengl::cg::program::transform_vertex(
			_vertex_declaration,
			_source
		);
}
#endif

sge::renderer::target::onscreen &
sge::opengl::device::onscreen_target() const
{
	return
		*onscreen_target_;
}

sge::renderer::caps::device const &
sge::opengl::device::caps() const
{
	return
		caps_;
}

sge::renderer::context::ffp_unique_ptr
sge::opengl::device::begin_rendering_ffp(
	sge::renderer::target::base &_target
)
{
	scoped_current_.get().begin_rendering();

	return
		sge::opengl::render_context::create(
			log_,
			context_,
			_target
		);
}

void
sge::opengl::device::end_rendering_ffp(
	sge::renderer::context::ffp &_context
)
{
	this->end_rendering(
		_context
	);
}

sge::renderer::state::ffp::alpha_test::object_unique_ptr
sge::opengl::device::create_alpha_test_state(
	sge::renderer::state::ffp::alpha_test::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::alpha_test::create(
			_parameters
		);
}

sge::renderer::state::ffp::clip_plane::object_unique_ptr
sge::opengl::device::create_clip_plane_state(
	sge::renderer::state::ffp::clip_plane::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::clip_plane::create(
			_parameters
		);
}

sge::renderer::state::ffp::fog::object_unique_ptr
sge::opengl::device::create_fog_state(
	sge::renderer::state::ffp::fog::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::fog::create(
			_parameters
		);
}

sge::renderer::state::ffp::lighting::object_unique_ptr
sge::opengl::device::create_lighting_state(
	sge::renderer::state::ffp::lighting::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::lighting::create(
			_parameters
		);
}

sge::renderer::state::ffp::lighting::light::object_unique_ptr
sge::opengl::device::create_light_state(
	sge::renderer::state::ffp::lighting::light::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::lighting::light::create(
			_parameters
		);
}

sge::renderer::state::ffp::lighting::material::object_unique_ptr
sge::opengl::device::create_material_state(
	sge::renderer::state::ffp::lighting::material::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::lighting::material::create(
			_parameters
		);
}

sge::renderer::state::ffp::misc::object_unique_ptr
sge::opengl::device::create_misc_state(
	sge::renderer::state::ffp::misc::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::misc::create(
			log_,
			context_,
			_parameters
		);
}

sge::renderer::state::ffp::sampler::object_unique_ptr
sge::opengl::device::create_ffp_sampler_state(
	sge::renderer::state::ffp::sampler::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::sampler::create(
			_parameters
		);
}

sge::renderer::state::ffp::transform::object_unique_ptr
sge::opengl::device::create_transform_state(
	sge::renderer::state::ffp::transform::parameters const &_parameters
)
{
	return
		sge::opengl::state::ffp::transform::create(
			context_,
			_parameters
		);
}

sge::renderer::display_mode::optional_object
sge::opengl::device::display_mode() const
{
	return
		device_state_->display_mode();
}

void
sge::opengl::device::display_mode(
	sge::renderer::display_mode::optional_object const &_display_mode
)
{
	device_state_->display_mode(
		_display_mode
	);
}

sge::renderer::display_mode::container
sge::opengl::device::display_modes() const
{
	return
		device_state_->display_modes();
}

sge::opengl::texture::basic_parameters
sge::opengl::device::texture_parameters()
{
	return
		sge::opengl::texture::basic_parameters(
			log_,
			context_
		);
}
