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


#include <sge/opengl/device.hpp>
#include <sge/opengl/index_buffer.hpp>
#include <sge/opengl/init_multi_sampling.hpp>
#include <sge/opengl/init_srgb.hpp>
#include <sge/opengl/onscreen_target.hpp>
#include <sge/opengl/vertex_buffer.hpp>
#include <sge/opengl/vertex_declaration.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/device_state/context.hpp>
#include <sge/opengl/device_state/create.hpp>
#include <sge/opengl/device_state/object.hpp>
#include <sge/opengl/device_state/system.hpp>
#include <sge/opengl/fbo/create_depth_stencil_surface.hpp>
#include <sge/opengl/fbo/create_target.hpp>
#include <sge/opengl/occlusion_query/create.hpp>
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
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/create_cube.hpp>
#include <sge/opengl/texture/create_depth_stencil.hpp>
#include <sge/opengl/texture/create_planar.hpp>
#include <sge/opengl/texture/create_volume.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface.hpp>
#include <sge/renderer/depth_stencil_surface_unique_ptr.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/index_buffer_unique_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/vertex_buffer_unique_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_unique_ptr.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
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
#include <sge/renderer/target/onscreen_fwd.hpp>
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
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

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
#endif


sge::opengl::device::device(
	sge::renderer::parameters::object const &_parameters,
	awl::window::object &_window,
	sge::opengl::device_state::system &_device_system,
	sge::opengl::context::system::object &_system_context,
	sge::renderer::caps::device const &_caps
)
:
	system_context_(
		_system_context
	),
	device_context_(),
	caps_(
		_caps
	),
	device_state_(
		sge::opengl::device_state::create(
			_parameters.display_mode(),
			_window
		)
	),
	context_(
		_device_system.create_context(
			_window
		)
	),
	scoped_current_(
		*context_
	),
	onscreen_target_(
		fcppt::make_unique_ptr<
			sge::opengl::onscreen_target
		>(
			fcppt::ref(
				device_context_
			),
			fcppt::ref(
				*context_
			),
			fcppt::ref(
				_window
			)
		)
	)
{
	_device_system.vsync(
		scoped_current_,
		_window,
		_parameters.vsync()
	);

	sge::opengl::init_multi_sampling(
		system_context_,
		_parameters.pixel_format().multi_samples()
	);

	sge::opengl::init_srgb(
		system_context_,
		_parameters.pixel_format().srgb()
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
		sge::renderer::context::core_unique_ptr(
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
			system_context_,
			device_context_
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

sge::renderer::depth_stencil_surface_unique_ptr
sge::opengl::device::create_depth_stencil_surface(
	sge::renderer::dim2 const &_dim,
	sge::renderer::depth_stencil_format::type const _type
)
{
	return
		sge::renderer::depth_stencil_surface_unique_ptr(
			sge::opengl::fbo::create_depth_stencil_surface(
				system_context_,
				_dim,
				_type
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

sge::renderer::vertex_declaration_unique_ptr
sge::opengl::device::create_vertex_declaration(
	sge::renderer::vf::dynamic::format const &_format
)
{
	return
		sge::renderer::vertex_declaration_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::vertex_declaration
			>(
				fcppt::ref(
					system_context_
				),
				fcppt::ref(
					device_context_
				),
				fcppt::cref(
					_format
				)
			)
		);
}

sge::renderer::vertex_buffer_unique_ptr
sge::opengl::device::create_vertex_buffer(
	sge::renderer::vertex_declaration const &_declaration,
	sge::renderer::vf::dynamic::part_index const _part,
	sge::renderer::vertex_count const _size,
	sge::renderer::resource_flags_field const &_flags
)
{
	return
		sge::renderer::vertex_buffer_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::vertex_buffer
			>(
				fcppt::ref(
					system_context_
				),
				_part,
				dynamic_cast<
					sge::opengl::vertex_declaration const &
				>(
					_declaration
				).format_part(
					_part
				),
				_size,
				_flags
			)
		);
}

sge::renderer::index_buffer_unique_ptr
sge::opengl::device::create_index_buffer(
	sge::renderer::index::dynamic::format::type const _format,
	sge::renderer::index_count const _size,
	sge::renderer::resource_flags_field const &_flags
)
{
	return
		sge::renderer::index_buffer_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::index_buffer
			>(
				fcppt::ref(
					system_context_
				),
				_format,
				_size,
				_flags
			)
		);
}

sge::renderer::occlusion_query::object_unique_ptr
sge::opengl::device::create_occlusion_query()
{
	return
		sge::opengl::occlusion_query::create(
			system_context_
		);
}

sge::renderer::state::core::blend::object_unique_ptr
sge::opengl::device::create_blend_state(
	sge::renderer::state::core::blend::parameters const &_parameters
)
{
	return
		sge::opengl::state::core::blend::create(
			system_context_,
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
			system_context_,
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
			system_context_,
			_parameters
		);
}

#if defined(SGE_RENDERER_HAVE_CG)
sge::cg::profile::object const
sge::opengl::device::create_cg_profile(
	sge::cg::profile::shader_type::type const _shader_type
)
{
	return
		sge::opengl::cg::profile::create(
			_shader_type
		);
}

sge::cg::program::compile_options const
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
			system_context_,
			device_context_,
			_parameter,
			_texture
		);
}

sge::cg::program::source const
sge::opengl::device::transform_cg_vertex_program(
	sge::renderer::vertex_declaration const &_vertex_declaration,
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
	return *onscreen_target_;
}

sge::renderer::caps::device const &
sge::opengl::device::caps() const
{
	return caps_;
}

sge::renderer::context::ffp_unique_ptr
sge::opengl::device::begin_rendering_ffp(
	sge::renderer::target::base &_target
)
{
	context_->begin_rendering();

	return
		sge::opengl::render_context::create(
			system_context_,
			device_context_,
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
			system_context_,
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
			system_context_,
			_parameters
		);
}

sge::renderer::display_mode::object const
sge::opengl::device::display_mode() const
{
	return
		device_state_->display_mode();
}

sge::opengl::texture::basic_parameters const
sge::opengl::device::texture_parameters()
{
	return
		sge::opengl::texture::basic_parameters(
			system_context_,
			device_context_
		);
}
