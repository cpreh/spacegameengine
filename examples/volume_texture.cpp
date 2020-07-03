//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/image/channel8.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/color/l8.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/luminance.hpp>
#include <sge/image3d/store/l8.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/input/event_base.hpp>
#include <sge/noise/sample.hpp>
#include <sge/noise/sample_parameters.hpp>
#include <sge/noise/simplex/object.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/func.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/variant.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/write_enable.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/variant.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>
#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <sge/renderer/state/core/sampler/address/mode_all.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/default.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/create_volume_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/set_proxy.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
#include <sge/renderer/vf/labels/texpos.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <mizuiro/image/algorithm/fill_indexed.hpp>
#include <mizuiro/image/algorithm/uninitialized.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <metal.hpp>
#include <array>
#include <chrono>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
sge::renderer::vf::pos<
	sge::renderer::scalar,
	3
>
vf_pos;

typedef
sge::renderer::vf::texpos<
	sge::renderer::scalar,
	3,
	sge::renderer::vf::index<
		0
	>
>
vf_texpos0;

typedef
sge::renderer::vf::texpos<
	sge::renderer::scalar,
	3,
	sge::renderer::vf::index<
		1
	>
>
vf_texpos1;

typedef
sge::renderer::vf::part<
	vf_pos,
	vf_texpos0,
	vf_texpos1
>
vf_part;

typedef
sge::renderer::vf::format<
	vf_part
>
vf_format;

typedef
vf_pos::packed_type
pos_vector;

typedef
std::array<
	pos_vector,
	2 * 3 * 6
>
pos_array;

void
fill_geometry(
	sge::renderer::vertex::buffer &_vertex_buffer
)
{
	pos_array const positions{{
		// bottom 1
		pos_vector(
			-1.f,-1.f,-1.f
		),
		pos_vector(
			-1.f,-1.f,1.f
		),
		pos_vector(
			1.f,-1.f,1.f
		),
		// bottom 2
		pos_vector(
			1.f,-1.f,1.f
		),
		pos_vector(
			1.f,-1.f,-1.f
		),
		pos_vector(
			-1.f,-1.f,-1.f
		),
		// top 1
		pos_vector(
			-1.f,1.f,-1.f
		),
		pos_vector(
			1.f,1.f,-1.f
		),
		pos_vector(
			1.f,1.f,1.f
		),
		// top 2
		pos_vector(
			1.f,1.f,1.f
		),
		pos_vector(
			-1.f,1.f,1.f
		),
		pos_vector(
			-1.f,1.f,-1.f
		),
		// left 1
		pos_vector(
			-1.f,-1.f,-1.f
		),
		pos_vector(
			-1.f,1.f,-1.f
		),
		pos_vector(
			-1.f,1.f,1.f
		),
		// left 2
		pos_vector(
			-1.f,1.f,1.f
		),
		pos_vector(
			-1.f,-1.f,1.f
		),
		pos_vector(
			-1.f,-1.f,-1.f
		),
		// right 1
		pos_vector(
			1.f,-1.f,-1.f
		),
		pos_vector(
			1.f,-1.f,1.f
		),
		pos_vector(
			1.f,1.f,1.f
		),
		// right 2
		pos_vector(
			1.f,1.f,1.f
		),
		pos_vector(
			1.f,1.f,-1.f
		),
		pos_vector(
			1.f,-1.f,-1.f
		),
		// front 1
		pos_vector(
			-1.f,-1.f,1.f
		),
		pos_vector(
			-1.f,1.f,1.f
		),
		pos_vector(
			1.f,1.f,1.f
		),
		// front 2
		pos_vector(
			1.f,1.f,1.f
		),
		pos_vector(
			1.f,-1.f,1.f
		),
		pos_vector(
			-1.f,-1.f,1.f
		),
		// back 1
		pos_vector(
			-1.f,-1.f,-1.f
		),
		pos_vector(
			1.f,-1.f,-1.f
		),
		pos_vector(
			1.f,1.f,-1.f
		),
		// back 2
		pos_vector(
			1.f,1.f,-1.f
		),
		pos_vector(
			-1.f,1.f,-1.f
		),
		pos_vector(
			-1.f,-1.f,-1.f
		)
	}};

	sge::renderer::vertex::scoped_lock const vb_lock(
		fcppt::make_ref(
			_vertex_buffer
		),
		sge::renderer::lock_mode::writeonly
	);

	typedef sge::renderer::vf::view<
		vf_part
	> vf_view;

	vf_view const view(
		vb_lock.value()
	);

	typedef vf_view::iterator vf_iterator;

	vf_iterator vb_it(
		view.begin()
	);

	// TODO: Use vf::vertex?
	for(
		auto const &position
		:
		positions
	)
	{
		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::pos{},
			position
		);

		pos_vector const texpos(
			fcppt::math::vector::map(
				position,
				[](
					sge::renderer::scalar const _value
				)
				{
					return
						static_cast<
							sge::renderer::scalar
						>(
							(_value + 1.f) / 2.f
						);
				}
			)
		);

		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::texpos<0>{},
			texpos
		);

		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::texpos<1>{},
			texpos
		);

		++vb_it;
	}
}

sge::renderer::texture::volume_unique_ptr
create_noise_texture(
	sge::renderer::device::core &_device
)
{
	typedef
	sge::image3d::store::l8
	store_type;

	typedef
	store_type::view_type
	view_type;

	typedef
	sge::noise::simplex::object<float,3>
	noise_type;

	typedef
	sge::noise::sample_parameters<noise_type>
	param_type;

	noise_type noise_generator(
		sge::noise::simplex::width(
			128u
		)
	);

	auto const make_color(
		[
			&noise_generator
		](
			view_type::dim const _current_position
		)
		{
			return
				sge::image::color::l8(
					sge::image::color::init::luminance()
					=
					static_cast<sge::image::channel8>(
						256.0f *
						(0.5f + 0.5f *
						sge::noise::sample(
							noise_generator,
							param_type(
								// TODO: Simplify this conversion
								param_type::position_type(
									noise_type::vector_type(
										fcppt::cast::int_to_float<
											noise_type::value_type
										>(
											_current_position.at_c<0>()
										),
										fcppt::cast::int_to_float<
											noise_type::value_type
										>(
											_current_position.at_c<1>()
										),
										fcppt::cast::int_to_float<
											noise_type::value_type
										>(
											_current_position.at_c<2>()
										)
									)
								),
								param_type::amplitude_type(
									0.8f
								),
								param_type::frequency_type(
									.005f
								),
								param_type::octaves_type(
									6u
								)
							)
						))
					)
				);
		}
	);

	store_type const store{
		store_type::dim(
			128u,
			128u,
			128u
		),
		store_type::init_function{
			[
				&make_color
			](
				view_type const &_view
			)
			{
				mizuiro::image::algorithm::fill_indexed(
					_view,
					[
						&make_color
					](
						view_type::dim const _current_position
					)
					{
						return
							make_color(
								_current_position
							);
					},
					mizuiro::image::algorithm::uninitialized::yes
				);
			}
		}
	};

	return
		sge::renderer::texture::create_volume_from_view(
			fcppt::make_ref(
				_device
			),
			sge::image3d::view::const_object(
				store.const_wrapped_view()
			),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::no
		);
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		sge::systems::with_window,
		sge::systems::with_renderer<
			sge::systems::renderer_caps::ffp
		>,
		sge::systems::with_input
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge volume texture example")
						)
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::d16,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::optional_resize_callback{
					sge::viewport::fill_on_resize()
				}
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field{
					sge::systems::cursor_option::exclusive
				}
			)
		)
	);

	sge::renderer::texture::volume_unique_ptr const texture(
		create_noise_texture(
			sys.renderer_device_core()
		)
	);

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
		sys.renderer_device_core().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					vf_format
				>()
			)
		)
	);

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer(
		sys.renderer_device_core().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				fcppt::make_cref(
					*vertex_declaration
				),
				sge::renderer::vf::dynamic::make_part_index<
					vf_format,
					vf_part
				>(),
				fcppt::strong_typedef_construct_cast<
					sge::renderer::vertex::count,
					fcppt::cast::static_cast_fun
				>(
					std::tuple_size<
						pos_array
					>::value
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	);

	::fill_geometry(
		*vertex_buffer
	);

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sge::camera::first_person::movement_speed(
				4.0f
			),
			sge::camera::coordinate_system::identity()
		)
	);

	sge::camera::perspective_projection_from_viewport camera_viewport_connection(
		fcppt::reference_to_base<
			sge::camera::has_mutable_projection
		>(
			fcppt::make_ref(
				camera
			)
		),
		fcppt::make_ref(
			sys.viewport_manager()
		),
		sge::renderer::projection::near(
			0.1f
		),
		sge::renderer::projection::far(
			1000.f
		),
		sge::renderer::projection::fov(
			fcppt::math::deg_to_rad(
				90.f
			)
		)
	);

	typedef
	sge::timer::basic<
		sge::timer::clocks::standard
	>
	timer;

	timer frame_timer(
		timer::parameters(
			std::chrono::seconds(
				1
			)
		)
	);

	sge::renderer::state::core::depth_stencil::object_unique_ptr const depth_stencil_state(
		sys.renderer_device_core().create_depth_stencil_state(
			sge::renderer::state::core::depth_stencil::parameters(
				sge::renderer::state::core::depth_stencil::depth::variant(
					sge::renderer::state::core::depth_stencil::depth::enabled(
						sge::renderer::state::core::depth_stencil::depth::func::less,
						sge::renderer::state::core::depth_stencil::depth::write_enable(
							true
						)
					)
				),
				sge::renderer::state::core::depth_stencil::stencil::variant(
					sge::renderer::state::core::depth_stencil::stencil::off()
				)
			)
		)
	);

	sge::renderer::state::core::sampler::object_unique_ptr const sampler_state(
		sys.renderer_device_core().create_sampler_state(
			sge::renderer::state::core::sampler::parameters(
				sge::renderer::state::core::sampler::address::mode_all(
					sge::renderer::state::core::sampler::address::mode::clamp
				),
				sge::renderer::state::core::sampler::filter::default_()
			)
		)
	);

	sge::renderer::state::core::sampler::const_object_ref_map const samplers{
		sge::renderer::state::core::sampler::const_object_ref_map::value_type{
			sge::renderer::texture::stage(
				0u
			),
			fcppt::make_cref(
				*sampler_state
			)
		},
		sge::renderer::state::core::sampler::const_object_ref_map::value_type{
			sge::renderer::texture::stage(
				1u
			),
			fcppt::make_cref(
				*sampler_state
			)
		}
	};


	auto const draw_camera(
		[
			&sys,
			&vertex_declaration,
			&texture,
			&vertex_buffer,
			&depth_stencil_state,
			&samplers,
			&camera
		](
			sge::renderer::context::ffp &_context,
			sge::camera::projection_matrix const &_projection_matrix
		)
		{
			sge::renderer::vertex::scoped_declaration const scoped_vd(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					fcppt::make_ref(
						_context
					)
				),
				fcppt::make_cref(
					*vertex_declaration
				)
			);

			sge::renderer::vertex::scoped_buffer const scoped_vb(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					fcppt::make_ref(
						_context
					)
				),
				fcppt::make_cref(
					*vertex_buffer
				)
			);

			sge::renderer::texture::scoped const scoped_texture1(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					fcppt::make_ref(
						_context
					)
				),
				fcppt::reference_to_base<
					sge::renderer::texture::base const
				>(
					fcppt::make_cref(
						*texture
					)
				),
				sge::renderer::texture::stage(
					0u
				)
			);

			sge::renderer::texture::scoped const scoped_texture2(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					fcppt::make_ref(
						_context
					)
				),
				fcppt::reference_to_base<
					sge::renderer::texture::base const
				>(
					fcppt::make_cref(
						*texture
					)
				),
				sge::renderer::texture::stage(
					1u
				)
			);

			sge::renderer::state::core::depth_stencil::scoped const scoped_depth_stencil(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					// TODO
					fcppt::make_ref(
						_context
					)
				),
				fcppt::make_cref(
					*depth_stencil_state
				)
			);

			sge::renderer::state::core::sampler::scoped const scoped_sampler(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					// TODO
					fcppt::make_ref(
						_context
					)
				),
				samplers
			);

			sge::renderer::state::ffp::transform::object_unique_ptr const projection_state(
				sys.renderer_device_ffp().create_transform_state(
					sge::renderer::state::ffp::transform::parameters(
						_projection_matrix.get()
					)
				)
			);

			sge::renderer::state::ffp::transform::object_unique_ptr const world_state(
				sys.renderer_device_ffp().create_transform_state(
					sge::renderer::state::ffp::transform::parameters(
						sge::camera::matrix_conversion::world(
							camera.coordinate_system()
						)
					)
				)
			);

			sge::renderer::state::ffp::transform::scoped const projection_transform(
				// TODO
				fcppt::make_ref(
					_context
				),
				sge::renderer::state::ffp::transform::mode::projection,
				fcppt::make_cref(
					*projection_state
				)
			);

			sge::renderer::state::ffp::transform::scoped const world_transform(
				// TODO
				fcppt::make_ref(
					_context
				),
				sge::renderer::state::ffp::transform::mode::world,
				fcppt::make_cref(
					*world_state
				)
			);

			_context.render_nonindexed(
				sge::renderer::vertex::first(
					0u
				),
				sge::renderer::vertex::count(
					vertex_buffer->linear_size()
				),
				sge::renderer::primitive_type::triangle_list
			);
		}
	);

	auto const draw(
		[
			&draw_camera,
			&camera,
			&frame_timer,
			&sys
		](
			sge::renderer::event::render const &
		)
		{
			camera.update(
				std::chrono::duration_cast<
					sge::camera::update_duration
				>(
					sge::timer::elapsed_and_reset(
						frame_timer
					)
				)
			);

			sge::renderer::context::scoped_ffp const scoped_block(
				fcppt::make_ref(
					sys.renderer_device_ffp()
				),
				fcppt::reference_to_base<
					sge::renderer::target::base
				>(
					fcppt::make_ref(
						sys.renderer_device_ffp().onscreen_target()
					)
				)
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
				.depth_buffer(
					1.f
				)
			);

			fcppt::optional::maybe_void(
				camera.projection_matrix(),
				[
					&draw_camera,
					&scoped_block
				](
					sge::camera::projection_matrix const &_projection
				)
				{
					draw_camera(
						scoped_block.get(),
						_projection
					);
				}
			);
		}
	);

	auto const process_event(
		[
			&sys,
			&draw,
			&camera
		](
			awl::event::base const &_event
		)
		{
			sge::systems::quit_on_escape(
				sys,
				_event
			);

			fcppt::optional::maybe_void(
				fcppt::variant::dynamic_cast_<
					metal::list<
						sge::renderer::event::render const,
						sge::input::event_base const
					>,
					fcppt::cast::dynamic_fun
				>(
					_event
				),
				[
					&draw,
					&camera
				](
					auto const &_variant
				)
				{
					fcppt::variant::match(
						_variant,
						[
							&draw
						](
							fcppt::reference<
								sge::renderer::event::render const
							> const _render_event
						)
						{
							draw(
								_render_event.get()
							);
						},
						[
							&camera
						](
							fcppt::reference<
								sge::input::event_base const
							> const _input_event
						)
						{
							camera.process_event(
								_input_event.get()
							);
						}
					);
				}
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&process_event
				](
					awl::event::base const &_event
				)
				{
					process_event(
						_event
					);
				}
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<<
		_error.string()
		<<
		FCPPT_TEXT('\n');

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<<
		_error.what()
		<<
		'\n';

	return
		awl::main::exit_failure();
}
