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


#include <sge/d3d9/create_device.hpp>
#include <sge/d3d9/device.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/index_buffer.hpp>
#include <sge/d3d9/multi_sample_quality.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <sge/d3d9/vertex_buffer.hpp>
#include <sge/d3d9/vertex_declaration.hpp>
#include <sge/d3d9/devicefuncs/begin_scene.hpp>
#include <sge/d3d9/devicefuncs/end_scene.hpp>
#include <sge/d3d9/devicefuncs/get_swap_chain.hpp>
#include <sge/d3d9/devicefuncs/reset.hpp>
#include <sge/d3d9/occlusion_query/create.hpp>
#include <sge/d3d9/parameters/create.hpp>
#include <sge/d3d9/render_context/create.hpp>
#include <sge/d3d9/render_context/needs_present.hpp>
#include <sge/d3d9/surface/depth_stencil.hpp>
#include <sge/d3d9/surface/depth_stencil_native.hpp>
#include <sge/d3d9/swapchainfuncs/present.hpp>
#include <sge/d3d9/state/core/defaults.hpp>
#include <sge/d3d9/state/core/blend/create.hpp>
#include <sge/d3d9/state/core/depth_stencil/create.hpp>
#include <sge/d3d9/state/core/rasterizer/create.hpp>
#include <sge/d3d9/state/core/sampler/create.hpp>
#include <sge/d3d9/target/offscreen.hpp>
#include <sge/d3d9/target/onscreen.hpp>
#include <sge/d3d9/texture/cube.hpp>
#include <sge/d3d9/texture/planar.hpp>
#include <sge/d3d9/texture/volume.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_unique_ptr.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/index_buffer_unique_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/vertex_buffer_unique_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_unique_ptr.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <sge/renderer/parameters/object.hpp>
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
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/target/onscreen_fwd.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_unique_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/time/sleep_any.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>


#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/d3d9/cg/profile/create.hpp>
#include <sge/d3d9/cg/program/create_loaded.hpp>
#include <sge/d3d9/cg/program/optimal_options.hpp>
#include <sge/d3d9/cg/program/transform_vertex.hpp>
#include <sge/d3d9/cg/texture/create_loaded.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#endif


sge::d3d9::device::device(
	IDirect3D9 *const _system,
	sge::renderer::device::parameters const &_parameters,
	sge::renderer::caps::device const &_caps
)
:
	sge::renderer::device::ffp(),
	srgb_(
		_parameters.params().pixel_format().srgb()
	),
	caps_(
		_caps
	),
	present_parameters_(
		sge::d3d9::parameters::create(
			_parameters.params(),
			_parameters.window()
		)
	),
	device_(
		sge::d3d9::create_device(
			_system,
			_parameters.adapter(),
			present_parameters_
		)
	),
	resources_(),
	swap_chain_(
		sge::d3d9::devicefuncs::get_swap_chain(
			*device_,
			0u
		)
	),
	onscreen_target_(
		fcppt::make_unique_ptr<
			sge::d3d9::target::onscreen
		>(
			fcppt::ref(
				*device_
			),
			// TODO: this must be inferred from the present_parameters!
			sge::image::color::format::bgrx8,
			sge::renderer::target::viewport(
				sge::renderer::pixel_rect(
					sge::renderer::pixel_rect::vector::null(),
					fcppt::math::dim::structure_cast<
						sge::renderer::pixel_rect::dim
					>(
						_parameters.window().size()
					)
				)
			),
			fcppt::ref(
				resources_
			),
			caps_.target_surfaces()
		)
	),
	default_core_states_(
		fcppt::make_unique_ptr<
			sge::d3d9::state::core::defaults
		>(
			fcppt::ref(
				*device_
			)
		)
	)
{
}

sge::d3d9::device::~device()
{
}

sge::renderer::context::core_unique_ptr
sge::d3d9::device::begin_rendering(
	sge::renderer::target::base &_target
)
{
	sge::d3d9::devicefuncs::begin_scene(
		*device_
	);

	return
		sge::d3d9::render_context::create(
			*device_,
			_target,
			caps_.texture_stages()
		);
}

void
sge::d3d9::device::end_rendering(
	sge::renderer::context::core &_context
)
{
	sge::d3d9::devicefuncs::end_scene(
		*device_
	);

	if(
		sge::d3d9::render_context::needs_present(
			_context
		)
	)
		if(
			!sge::d3d9::swapchainfuncs::present(
				*swap_chain_,
				srgb_
			)
		)
			this->reset();
}

sge::renderer::target::offscreen_unique_ptr
sge::d3d9::device::create_target()
{
	return
		sge::renderer::target::offscreen_unique_ptr(
			fcppt::make_unique_ptr<
				sge::d3d9::target::offscreen
			>(
				fcppt::ref(
					*device_
				),
				caps_.target_surfaces()
			)
		);
}

sge::renderer::texture::planar_unique_ptr
sge::d3d9::device::create_planar_texture(
	sge::renderer::texture::planar_parameters const &_param
)
{
	return
		sge::renderer::texture::planar_unique_ptr(
			this->add_resource<
				sge::d3d9::texture::planar
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::texture::planar
				>(
					fcppt::ref(
						*device_
					),
					_param
				)
			)
		);
}

sge::renderer::texture::depth_stencil_unique_ptr
sge::d3d9::device::create_depth_stencil_texture(
	sge::renderer::texture::depth_stencil_parameters const &_params
)
{
	return
		sge::renderer::texture::depth_stencil_unique_ptr();
#if 0
	return
		this->add_resource<
			d3d9::texture::depth_stencil
		>(
			fcppt::make_shared_ptr<
				d3d9::texture::depth_stencil
			>(
				device_.get(),
				_params
			)
		);
#endif
}

sge::renderer::depth_stencil_surface_unique_ptr
sge::d3d9::device::create_depth_stencil_surface(
	sge::renderer::dim2 const &_dim,
	sge::renderer::depth_stencil_format::type const _format
)
{
	return
		sge::renderer::depth_stencil_surface_unique_ptr(
			this->add_resource<
				sge::d3d9::surface::depth_stencil
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::surface::depth_stencil
				>(
					fcppt::make_unique_ptr<
						sge::d3d9::surface::depth_stencil_native
					>(
						fcppt::ref(
							*device_
						),
						_dim,
						_format,
						present_parameters_.MultiSampleType,
						sge::d3d9::multi_sample_quality(
							present_parameters_.MultiSampleQuality
						)
					),
					sge::d3d9::needs_reset::yes
				)
			)
		);
}

sge::renderer::texture::volume_unique_ptr
sge::d3d9::device::create_volume_texture(
	sge::renderer::texture::volume_parameters const &_param
)
{
	return
		sge::renderer::texture::volume_unique_ptr(
			this->add_resource<
				sge::d3d9::texture::volume
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::texture::volume
				>(
					fcppt::ref(
						*device_
					),
					_param
				)
			)
		);
}

sge::renderer::texture::cube_unique_ptr
sge::d3d9::device::create_cube_texture(
	sge::renderer::texture::cube_parameters const &_param
)
{
	return
		sge::renderer::texture::cube_unique_ptr(
			this->add_resource<
				sge::d3d9::texture::cube
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::texture::cube
				>(
					fcppt::ref(
						*device_
					),
					_param
				)
			)
		);
}

sge::renderer::vertex_declaration_unique_ptr
sge::d3d9::device::create_vertex_declaration(
	sge::renderer::vf::dynamic::format const &_format
)
{
	return
		sge::renderer::vertex_declaration_unique_ptr(
			fcppt::make_unique_ptr<
				sge::d3d9::vertex_declaration
			>(
				fcppt::ref(
					*device_
				),
				_format
			)
		);
}

sge::renderer::vertex_buffer_unique_ptr
sge::d3d9::device::create_vertex_buffer(
	sge::renderer::vertex_declaration const &_declaration,
	sge::renderer::vf::dynamic::part_index const _part,
	sge::renderer::vertex_count const _size,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	return
		sge::renderer::vertex_buffer_unique_ptr(
			this->add_resource<
				sge::d3d9::vertex_buffer
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::vertex_buffer
				>(
					fcppt::ref(
						*device_
					),
					dynamic_cast<
						sge::d3d9::vertex_declaration const &
					>(
						_declaration
					).format().parts().at(
						_part.get()
					),
					_part,
					_size,
					_resource_flags
				)
			)
		);
}

sge::renderer::index_buffer_unique_ptr
sge::d3d9::device::create_index_buffer(
	sge::renderer::index::dynamic::format::type const _format,
	sge::renderer::index_count const _size,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	return
		sge::renderer::index_buffer_unique_ptr(
			this->add_resource<
				sge::d3d9::index_buffer
			>(
				fcppt::make_unique_ptr<
					sge::d3d9::index_buffer
				>(
					fcppt::ref(
						*device_
					),
					_format,
					_size,
					_resource_flags
				)
			)
		);
}

sge::renderer::occlusion_query::object_unique_ptr
sge::d3d9::device::create_occlusion_query()
{
	return
		sge::d3d9::occlusion_query::create(
			*device_
		);
}

sge::renderer::state::core::blend::object_unique_ptr
sge::d3d9::device::create_blend_state(
	sge::renderer::state::core::blend::parameters const &_parameters
)
{
	return
		sge::d3d9::state::core::blend::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::core::depth_stencil::object_unique_ptr
sge::d3d9::device::create_depth_stencil_state(
	sge::renderer::state::core::depth_stencil::parameters const &_parameters
)
{
	return
		sge::d3d9::state::core::depth_stencil::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::core::rasterizer::object_unique_ptr
sge::d3d9::device::create_rasterizer_state(
	sge::renderer::state::core::rasterizer::parameters const &_parameters
)
{
	return
		sge::d3d9::state::core::rasterizer::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::core::sampler::object_unique_ptr
sge::d3d9::device::create_sampler_state(
	sge::renderer::state::core::sampler::parameters const &_parameters
)
{
	return
		sge::d3d9::state::core::sampler::create(
			*device_,
			_parameters
		);
}

#if defined(SGE_RENDERER_HAVE_CG)
sge::cg::profile::object const
sge::d3d9::device::create_cg_profile(
	sge::cg::profile::shader_type::type const _shader_type
)
{
	return
		sge::d3d9::cg::profile::create(
			*device_,
			_shader_type
		);
}

sge::cg::program::compile_options const
sge::d3d9::device::cg_compile_options(
	sge::cg::context::object const &,
	sge::cg::profile::object const &_profile
)
{
	return
		sge::d3d9::cg::program::optimal_options(
			*device_,
			_profile
		);
}

sge::renderer::cg::loaded_program_unique_ptr
sge::d3d9::device::load_cg_program(
	sge::cg::program::object &_program
)
{
	return
		sge::d3d9::cg::program::create_loaded(
			*device_,
			_program
		);
}

sge::renderer::cg::loaded_texture_unique_ptr
sge::d3d9::device::load_cg_texture(
	sge::cg::parameter::object const &_parameter,
	sge::renderer::texture::base &_texture
)
{
	return
		sge::d3d9::cg::texture::create_loaded(
			*device_,
			_parameter,
			_texture,
			caps_.texture_stages()
		);
}

sge::cg::program::source const
sge::d3d9::device::transform_cg_vertex_program(
	sge::renderer::vertex_declaration const &_vertex_declaration,
	sge::cg::program::source const &_source
)
{
	return
		sge::d3d9::cg::program::transform_vertex(
			_vertex_declaration,
			_source
		);
}
#endif

sge::renderer::target::onscreen &
sge::d3d9::device::onscreen_target() const
{
	return *onscreen_target_;
}

sge::renderer::caps::device const &
sge::d3d9::device::caps() const
{
	return caps_;
}

template<
	typename Ptr
>
fcppt::unique_ptr<
	Ptr
>
sge::d3d9::device::add_resource(
	fcppt::unique_ptr<
		Ptr
	> _ptr
)
{
	resources_.add(
		*_ptr
	);

	return
		fcppt::move(
			_ptr
		);
}

void
sge::d3d9::device::reinit()
{
	resources_.reinit();
}

void
sge::d3d9::device::release()
{
	resources_.release();
}

void
sge::d3d9::device::reset()
{
	this->release();

	while(
		device_->TestCooperativeLevel()
		== D3DERR_DEVICELOST
		||
		!sge::d3d9::devicefuncs::reset(
			*device_,
			present_parameters_
		)
	)
		fcppt::time::sleep_any(
			boost::chrono::milliseconds(
				1
			)
		);

	this->reinit();
}
