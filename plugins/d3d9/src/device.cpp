//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/create_device.hpp>
#include <sge/d3d9/current_display_mode.hpp>
#include <sge/d3d9/device.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/get_device_caps.hpp>
#include <sge/d3d9/get_display_modes.hpp>
#include <sge/d3d9/index_buffer.hpp>
#include <sge/d3d9/multi_sample_quality.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <sge/d3d9/devicefuncs/begin_scene.hpp>
#include <sge/d3d9/devicefuncs/end_scene.hpp>
#include <sge/d3d9/devicefuncs/get_swap_chain.hpp>
#include <sge/d3d9/devicefuncs/reset.hpp>
#include <sge/d3d9/occlusion_query/create.hpp>
#include <sge/d3d9/parameters/create.hpp>
#include <sge/d3d9/parameters/extract_pixel_format.hpp>
#include <sge/d3d9/parameters/extract_srgb.hpp>
#include <sge/d3d9/parameters/convert/bit_depth.hpp>
#include <sge/d3d9/render_context/create.hpp>
#include <sge/d3d9/render_context/needs_present.hpp>
#include <sge/d3d9/render_context/parameters.hpp>
#include <sge/d3d9/surface/depth_stencil_offscreen.hpp>
#include <sge/d3d9/swapchainfuncs/present.hpp>
#include <sge/d3d9/state/core/defaults.hpp>
#include <sge/d3d9/state/core/blend/create.hpp>
#include <sge/d3d9/state/core/depth_stencil/create.hpp>
#include <sge/d3d9/state/core/rasterizer/create.hpp>
#include <sge/d3d9/state/core/sampler/create.hpp>
#include <sge/d3d9/state/ffp/defaults.hpp>
#include <sge/d3d9/state/ffp/alpha_test/create.hpp>
#include <sge/d3d9/state/ffp/clip_plane/create.hpp>
#include <sge/d3d9/state/ffp/fog/create.hpp>
#include <sge/d3d9/state/ffp/lighting/create.hpp>
#include <sge/d3d9/state/ffp/lighting/light/create.hpp>
#include <sge/d3d9/state/ffp/lighting/material/create.hpp>
#include <sge/d3d9/state/ffp/misc/create.hpp>
#include <sge/d3d9/state/ffp/sampler/create.hpp>
#include <sge/d3d9/state/ffp/transform/create.hpp>
#include <sge/d3d9/target/offscreen.hpp>
#include <sge/d3d9/target/onscreen.hpp>
#include <sge/d3d9/texture/cube.hpp>
#include <sge/d3d9/texture/planar.hpp>
#include <sge/d3d9/texture/volume.hpp>
#include <sge/d3d9/vertex/buffer.hpp>
#include <sge/d3d9/vertex/declaration.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/draw_timer_setting_opt.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/event/render.hpp>
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
#include <sge/renderer/target/onscreen_fwd.hpp>
#include <sge/renderer/target/viewport.hpp>
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
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_event_function.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/processor.hpp>
#include <awl/timer/match.hpp>
#include <awl/timer/object.hpp>
#include <awl/window/object.hpp>
#include <awl/window/event/base.hpp>
#include <awl/window/event/resize.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <thread>
#include <utility>
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
#include <sge/renderer/vertex/declaration_fwd.hpp>
#endif


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::d3d9::device::device(
	IDirect3D9 &_system,
	fcppt::log::object &_log,
	sge::renderer::device::parameters const &_parameters
)
:
	sge::renderer::device::ffp(),
	index_(
		fcppt::cast::to_unsigned(
			D3DADAPTER_DEFAULT
		)
	),
	srgb_(
		sge::d3d9::parameters::extract_srgb(
			_parameters.window().awl_object().visual()
		)
	),
	caps_(
		sge::d3d9::get_device_caps(
			_system,
			index_
		)
	),
	present_parameters_(
		sge::d3d9::parameters::create(
			sge::d3d9::parameters::extract_pixel_format(
				_parameters.window().awl_object().visual()
			),
			_parameters.display_mode(),
			_parameters.window().awl_object()
		)
	),
	device_(
		sge::d3d9::create_device(
			_system,
			index_,
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
			*device_,
			// TODO: this must be inferred from the present_parameters!
			sge::image::color::format::bgrx8,
			sge::renderer::target::viewport(
				sge::renderer::pixel_rect(
					fcppt::math::vector::null<
						sge::renderer::pixel_rect::vector
					>(),
					fcppt::math::dim::structure_cast<
						sge::renderer::pixel_rect::dim,
						fcppt::cast::size_fun
					>(
						fcppt::math::dim::to_signed(
							_parameters.window().size()
						)
					)
				)
			),
			resources_,
			caps_.target_surfaces()
		)
	),
	core_defaults_(
		fcppt::make_unique_ptr<
			sge::d3d9::state::core::defaults
		>(
			*device_
		)
	),
	ffp_defaults_(
		fcppt::make_unique_ptr<
			sge::d3d9::state::ffp::defaults
		>(
			*device_
		)
	),
	display_modes_(
		sge::d3d9::get_display_modes(
			_system,
			index_,
			sge::d3d9::parameters::convert::bit_depth(
				sge::d3d9::parameters::extract_pixel_format(
					_parameters.window().awl_object().visual()
				).color()
			)
		)
	),
	window_{
		_parameters.window()
	},
	draw_timer_{
		// TODO: How do we know when this changes?
		_parameters.window().system().awl_system().processor().create_timer(
			sge::renderer::display_mode::draw_timer_setting_opt(
				_log,
				this->display_mode()
			)
		)
	},
	window_event_connection_{
		_parameters.window().event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				{
					return
						this->on_window_event(
							_event
						);
				}
			}
		)
	},
	system_event_connection_{
		_parameters.window().system().event_handler(
			sge::window::system_event_function{
				[
					this
				](
					awl::event::base const &_event
				)
				{
					return
						this->on_system_event(
							_event
						);
				}
			}
		)
	}
{
}

FCPPT_PP_POP_WARNING

sge::d3d9::device::~device()
{
}

sge::renderer::context::core_unique_ptr
sge::d3d9::device::begin_rendering(
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
		fcppt::unique_ptr_to_base<
			sge::renderer::target::offscreen
		>(
			fcppt::make_unique_ptr<
				sge::d3d9::target::offscreen
			>(
				*device_,
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
		fcppt::unique_ptr_to_base<
			sge::renderer::texture::planar
		>(
			this->add_resource(
				fcppt::make_unique_ptr<
					sge::d3d9::texture::planar
				>(
					*device_,
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
	// FIXME
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("Depth stencil textures are not implenented.")
	);
}

sge::renderer::depth_stencil_buffer::surface_unique_ptr
sge::d3d9::device::create_depth_stencil_surface(
	sge::renderer::depth_stencil_buffer::surface_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::depth_stencil_buffer::surface
		>(
			this->add_resource(
				fcppt::make_unique_ptr<
					sge::d3d9::surface::depth_stencil_offscreen
				>(
					*device_,
					_parameters,
					present_parameters_.MultiSampleType,
					sge::d3d9::multi_sample_quality(
						present_parameters_.MultiSampleQuality
					)
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
		fcppt::unique_ptr_to_base<
			sge::renderer::texture::volume
		>(
			this->add_resource(
				fcppt::make_unique_ptr<
					sge::d3d9::texture::volume
				>(
					*device_,
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
		fcppt::unique_ptr_to_base<
			sge::renderer::texture::cube
		>(
			this->add_resource(
				fcppt::make_unique_ptr<
					sge::d3d9::texture::cube
				>(
					*device_,
					_param
				)
			)
		);
}

sge::renderer::vertex::declaration_unique_ptr
sge::d3d9::device::create_vertex_declaration(
	sge::renderer::vertex::declaration_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::vertex::declaration
		>(
			fcppt::make_unique_ptr<
				sge::d3d9::vertex::declaration
			>(
				*device_,
				_parameters
			)
		);
}

sge::renderer::vertex::buffer_unique_ptr
sge::d3d9::device::create_vertex_buffer(
	sge::renderer::vertex::buffer_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::vertex::buffer
		>(
			this->add_resource(
				fcppt::make_unique_ptr<
					sge::d3d9::vertex::buffer
				>(
					*device_,
					fcppt::cast::static_downcast<
						sge::d3d9::vertex::declaration const &
					>(
						_parameters.declaration()
					).format().parts().at(
						_parameters.part().get()
					),
					_parameters
				)
			)
		);
}

sge::renderer::index::buffer_unique_ptr
sge::d3d9::device::create_index_buffer(
	sge::renderer::index::buffer_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::index::buffer
		>(
			this->add_resource(
				fcppt::make_unique_ptr<
					sge::d3d9::index_buffer
				>(
					*device_,
					_parameters
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
sge::cg::profile::object
sge::d3d9::device::create_cg_profile(
	sge::cg::profile::shader_type const _shader_type
)
{
	return
		sge::d3d9::cg::profile::create(
			*device_,
			_shader_type
		);
}

sge::cg::program::compile_options
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

sge::cg::program::source
sge::d3d9::device::transform_cg_vertex_program(
	sge::renderer::vertex::declaration const &_vertex_declaration,
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
	return
		*onscreen_target_;
}

sge::renderer::caps::device const &
sge::d3d9::device::caps() const
{
	return
		caps_;
}

sge::renderer::display_mode::optional_object
sge::d3d9::device::display_mode() const
{
	return
		sge::renderer::display_mode::optional_object(
			sge::d3d9::current_display_mode(
				*device_
			)
		);
}

void
sge::d3d9::device::fullscreen(
	sge::renderer::display_mode::optional_fullscreen const &_fullscreen
)
{
	// TODO
}

sge::renderer::display_mode::container
sge::d3d9::device::display_modes() const
{
	return
		display_modes_;
}

sge::renderer::context::ffp_unique_ptr
sge::d3d9::device::begin_rendering_ffp(
	sge::renderer::target::base &_target
)
{
	sge::d3d9::devicefuncs::begin_scene(
		*device_
	);

	return
		sge::d3d9::render_context::create(
			sge::d3d9::render_context::parameters(
				*device_,
				_target,
				caps_.texture_stages(),
				caps_.light_indices(),
				*core_defaults_,
				*ffp_defaults_
			)
		);
}

void
sge::d3d9::device::end_rendering_ffp(
	sge::renderer::context::ffp &_context
)
{
	this->end_rendering(
		_context
	);
}

sge::renderer::state::ffp::alpha_test::object_unique_ptr
sge::d3d9::device::create_alpha_test_state(
	sge::renderer::state::ffp::alpha_test::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::alpha_test::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::ffp::clip_plane::object_unique_ptr
sge::d3d9::device::create_clip_plane_state(
	sge::renderer::state::ffp::clip_plane::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::clip_plane::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::ffp::fog::object_unique_ptr
sge::d3d9::device::create_fog_state(
	sge::renderer::state::ffp::fog::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::fog::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::ffp::lighting::object_unique_ptr
sge::d3d9::device::create_lighting_state(
	sge::renderer::state::ffp::lighting::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::lighting::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::ffp::lighting::light::object_unique_ptr
sge::d3d9::device::create_light_state(
	sge::renderer::state::ffp::lighting::light::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::lighting::light::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::ffp::lighting::material::object_unique_ptr
sge::d3d9::device::create_material_state(
	sge::renderer::state::ffp::lighting::material::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::lighting::material::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::ffp::misc::object_unique_ptr
sge::d3d9::device::create_misc_state(
	sge::renderer::state::ffp::misc::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::misc::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::ffp::sampler::object_unique_ptr
sge::d3d9::device::create_ffp_sampler_state(
	sge::renderer::state::ffp::sampler::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::sampler::create(
			*device_,
			_parameters
		);
}

sge::renderer::state::ffp::transform::object_unique_ptr
sge::d3d9::device::create_transform_state(
	sge::renderer::state::ffp::transform::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::transform::create(
			*device_,
			_parameters
		);
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
	> &&_ptr
)
{
	resources_.add(
		*_ptr
	);

	return
		std::move(
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
		std::this_thread::sleep_for(
			std::chrono::milliseconds(
				1
			)
		);

	this->reinit();
}

awl::event::container
sge::d3d9::device::on_window_event(
	awl::window::event::base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic<
			awl::window::event::resize const
		>(
			_event
		),
		[
			this
		](
			fcppt::reference<
				awl::window::event::resize const
			> const _resize
		)
		{
			this->on_resize(
				_resize.get()
			);
		}
	);

	return
		awl::event::container{};
}

awl::event::container
sge::d3d9::device::on_system_event(
	awl::event::base const &_event
)
{
	return
		fcppt::optional::to_container<
			awl::event::container
		>(
			fcppt::optional::make_if(
				awl::timer::match(
					_event,
					*draw_timer_
				),
				[
					this
				]{
					return
						fcppt::unique_ptr_to_base<
							awl::event::base
						>(
							fcppt::make_unique_ptr<
								sge::renderer::event::render
							>(
								fcppt::make_ref(
									this->window_.awl_object()
								)
							)
						);
				}
			)
		);
}

void
sge::d3d9::device::on_resize(
	awl::window::event::resize const &_resize
)
{
	if(
		present_parameters_.Windowed
		==
		FALSE
	)
		return;

	if(
		fcppt::math::dim::contents(
			_resize.dim()
		)
		==
		0u
	)
		return;

	present_parameters_.BackBufferWidth =
		_resize.dim().w();

	present_parameters_.BackBufferHeight =
		_resize.dim().h();

	this->reset();
}
