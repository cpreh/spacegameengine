//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/string.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/l8.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/luminance.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/algorithm/copy.hpp>
#include <sge/image2d/store/l8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/key/code_to_digit.hpp>
#include <sge/input/key/digit.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
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
#include <sge/renderer/state/core/sampler/const_object_ref.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/scoped_single.hpp>
#include <sge/renderer/state/core/sampler/address/default.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/linear.hpp>
#include <sge/renderer/state/core/sampler/filter/mipmap.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/point.hpp>
#include <sge/renderer/state/core/sampler/filter/trilinear.hpp>
#include <sge/renderer/state/core/sampler/filter/variant.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/level.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_is_null.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/mipmap/all_levels.hpp>
#include <sge/renderer/texture/mipmap/auto_generate.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/geometry/update_one.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/no_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
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
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/frames_counter.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/output_to_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unique_ptr_to_const.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/dynamic_cast.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <metal.hpp>
#include <array>
#include <chrono>
#include <exception>
#include <utility>
#include <fcppt/config/external_end.hpp>


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
		sge::systems::with_input,
		sge::systems::with_font
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge texture filter example")
						)
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
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

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sge::camera::first_person::movement_speed(
				4.0f
			),
			sge::camera::coordinate_system::identity()
		)
	);

	sge::image::size_type const block_element_size(
		32u
	);

	sge::image2d::dim const block_size(
		fcppt::math::dim::fill<
			sge::image2d::dim
		>(
			block_element_size
		)
	);

	sge::image::size_type const num_blocks(
		2u
	);

	typedef
	sge::image2d::store::l8
	store_type;

	store_type const whole_store{
		block_size
		*
		num_blocks,
		store_type::init_function{
			[
				block_size
			](
				store_type::view_type const &_view
			)
			{
				store_type const white_store(
					block_size,
					sge::image::color::l8(
						sge::image::color::init::luminance() %= 1.
					)
				);

				store_type const black_store(
					block_size,
					sge::image::color::l8(
						sge::image::color::init::luminance() %= 0.
					)
				);

				for(
					sge::image::size_type const y
					:
					fcppt::make_int_range_count(
						num_blocks
					)
				)
					for(
						sge::image::size_type const x
						:
						fcppt::make_int_range_count(
							num_blocks
						)
					)
						sge::image2d::algorithm::copy(
							sge::image2d::view::const_object(
								(((x + y) % 2u) == 0u)
								?
									white_store.wrapped_view()
								:
									black_store.wrapped_view()
							),
							sge::image2d::view::sub(
								sge::image2d::view::object(
									sge::image::view::wrap(
										_view
									)
								),
								sge::image2d::rect(
									sge::image2d::rect::vector(
										x,
										y
									)
									*
									block_size,
									block_size
								)
							),
							sge::image::algorithm::may_overlap::no,
							sge::image::algorithm::uninitialized::yes
						);
			}
		}
	};

	sge::renderer::state::core::sampler::filter::anisotropic::level const anisotropy(
		sys.renderer_device_core().caps().max_anisotropy().get()
	);

	sge::font::string const anisotropy_string(
		SGE_FONT_LIT(' ')
		+
		fcppt::output_to_string<
			sge::font::string
		>(
			anisotropy
		)
		+
		SGE_FONT_LIT('x')
	);

	auto const make_sampler_parameters(
		[](
			sge::renderer::state::core::sampler::filter::parameters const &_filter
		)
		-> sge::renderer::state::core::sampler::parameters
		{
			return
				sge::renderer::state::core::sampler::parameters(
					sge::renderer::state::core::sampler::address::default_(),
					_filter
				);
		}
	);

	auto const make_anisotropic_sampler_parameters(
		[
			make_sampler_parameters
		](
			sge::renderer::state::core::sampler::filter::anisotropic::mip const _mip,
			sge::renderer::state::core::sampler::filter::anisotropic::level const _level
		)
		-> sge::renderer::state::core::sampler::parameters
		{
			return
				make_sampler_parameters(
					sge::renderer::state::core::sampler::filter::parameters(
						sge::renderer::state::core::sampler::filter::variant{
							sge::renderer::state::core::sampler::filter::anisotropic::parameters(
								_mip,
								_level
							)
						}
					)
				);
		}
	);

	sge::renderer::state::core::sampler::object_unique_ptr const
		point_sampler(
			sys.renderer_device_core().create_sampler_state(
				make_sampler_parameters(
					sge::renderer::state::core::sampler::filter::point()
				)
			)
		),
		linear_sampler(
			sys.renderer_device_core().create_sampler_state(
				make_sampler_parameters(
					sge::renderer::state::core::sampler::filter::linear()
				)
			)
		),
		mipmap_sampler(
			sys.renderer_device_core().create_sampler_state(
				make_sampler_parameters(
					sge::renderer::state::core::sampler::filter::mipmap()
				)
			)
		),
		trilinear_sampler(
			sys.renderer_device_core().create_sampler_state(
				make_sampler_parameters(
					sge::renderer::state::core::sampler::filter::trilinear()
				)
			)
		),
		anisotropic_sampler(
			sys.renderer_device_core().create_sampler_state(
				make_anisotropic_sampler_parameters(
					sge::renderer::state::core::sampler::filter::anisotropic::mip::off,
					anisotropy
				)
			)
		),
		anisotropic_mipmap_sampler(
			sys.renderer_device_core().create_sampler_state(
				make_anisotropic_sampler_parameters(
					sge::renderer::state::core::sampler::filter::anisotropic::mip::point,
					anisotropy
				)
			)
		),
		anisotropic_trilinear_sampler(
			sys.renderer_device_core().create_sampler_state(
				make_anisotropic_sampler_parameters(
					sge::renderer::state::core::sampler::filter::anisotropic::mip::linear,
					anisotropy
				)
			)
		);

	typedef
	std::pair<
		sge::font::string,
		sge::renderer::state::core::sampler::const_object_ref
	>
	string_filter_pair;

	typedef
	std::array<
		string_filter_pair,
		7u
	>
	filter_array;

	filter_array const filters{{
		std::make_pair(
			SGE_FONT_LIT("point"),
			fcppt::make_cref(
				*point_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("linear"),
			fcppt::make_cref(
				*linear_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("mipmap"),
			fcppt::make_cref(
				*mipmap_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("trilinear"),
			fcppt::make_cref(
				*trilinear_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("anisotropic")
			+
			anisotropy_string,
			fcppt::make_cref(
				*anisotropic_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("anisotropic")
			+
			anisotropy_string
			+
			SGE_FONT_LIT(" + mipmap"),
			fcppt::make_cref(
				*anisotropic_mipmap_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("anisotropic")
			+
			anisotropy_string
			+
			SGE_FONT_LIT(" + trilinear"),
			fcppt::make_cref(
				*anisotropic_trilinear_sampler
			)
		)
	}};

	typedef
	sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::pos<
			sge::sprite::config::pos_option::pos
		>,
		sge::sprite::config::normal_size<
			sge::sprite::config::texture_size_option::never
		>,
		metal::list<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::repetition,
				sge::sprite::config::texture_ownership::unique
			>
		>
	>
	sprite_choices;

	typedef
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	>
	sprite_buffers_type;

	typedef
	sge::sprite::object<
		sprite_choices
	>
	sprite_object;

	typedef
	sge::sprite::state::no_choices
	sprite_state_choices;

	typedef
	sge::sprite::state::object<
		sprite_state_choices
	>
	sprite_state_object;

	typedef
	sge::sprite::state::parameters<
		sprite_state_choices
	>
	sprite_state_parameters;

	sprite_buffers_type sprite_buffers(
		sys.renderer_device_core(),
		sge::sprite::buffers::option::static_
	);

	sprite_state_object sprite_states(
		sys.renderer_device_ffp(),
		sprite_state_parameters()
	);

	sprite_object::unit const sprite_size(
		2000
	);

	sprite_object::repetition_type::value_type const repetition(
		fcppt::cast::int_to_float<
			sprite_object::repetition_type::value_type
		>(
			sprite_size / 5
		)
	);

	sprite_object const sprite(
		sge::sprite::roles::pos{} =
			fcppt::math::vector::fill<
				sprite_object::vector
			>(
				-(sprite_size / 2)
			),
		sge::sprite::roles::size{} =
			fcppt::math::dim::fill<
				sprite_object::dim
			>(
				sprite_size
			),
		sge::sprite::roles::repetition{} =
			fcppt::math::vector::fill<
				sprite_object::repetition_type
			>(
				repetition
			),
		sge::sprite::roles::texture0{} =
			sprite_object::texture_type{
				fcppt::unique_ptr_to_const(
					fcppt::unique_ptr_to_base<
						sge::texture::part
					>(
						fcppt::make_unique_ptr<
							sge::texture::part_raw_ptr
						>(
							sge::renderer::texture::create_planar_from_view(
								sys.renderer_device_core(),
								sge::image2d::view::const_object(
									whole_store.const_wrapped_view()
								),
								sge::renderer::texture::mipmap::all_levels(
									sge::renderer::texture::mipmap::auto_generate::yes
								),
								sge::renderer::resource_flags_field::null(),
								sge::renderer::texture::emulate_srgb::no
							)
						)
					)
				)
			}
	);

	typedef
	sge::sprite::render::range<
		sprite_choices
	>
	sprite_range_type;

	sprite_range_type const sprite_range(
		sge::sprite::geometry::update_one(
			sprite,
			sprite_buffers
		)
	);

	fcppt::reference<
		filter_array::value_type const
	> current_filter{
		std::get<
			0
		>(
			filters
		)
	};

	auto const key_event(
		[
			&filters,
			&current_filter
		](
			sge::input::keyboard::event::key const &_event
		)
		{
			if(
				!_event.pressed()
			)
				return;

			fcppt::optional::maybe_void(
				sge::input::key::code_to_digit(
					_event.get().code()
				),
				[
					&filters,
					&current_filter
				](
					sge::input::key::digit const _digit
				)
				{
					fcppt::optional::maybe_void(
						fcppt::container::at_optional(
							filters,
							filter_array::size_type{
								_digit.get()
								-
								1u
							}
						),
						[
							&current_filter
						](
							fcppt::reference<
								filter_array::value_type const
							> const _filter
						)
						{
							current_filter =
								_filter;
						}
					);
				}
			);
		}
	);

	sge::camera::perspective_projection_from_viewport camera_viewport_connection(
		camera,
		sys.viewport_manager(),
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

	sge::timer::basic<
		sge::timer::clocks::standard
	> frame_timer(
		sge::timer::parameters<
			sge::timer::clocks::standard
		>(
			std::chrono::seconds(
				1
			)
		)
	);

	sge::timer::frames_counter frames_counter;

	sge::font::string const text_appendix(
		SGE_FONT_LIT(" (Press 1 through ")
		+
		fcppt::output_to_string<
			sge::font::string
		>(
			filters.size()
		)
		+
		SGE_FONT_LIT(" to select a filter!)")
	);

	sge::font::object_unique_ptr const font(
		sys.font_system().create_font(
			sge::font::parameters()
				.family(
					FCPPT_TEXT("sans")
				)
		)
	);

	auto const draw_camera(
		[
			&frames_counter,
			&text_appendix,
			&font,
			&sprite_buffers,
			&sprite_range,
			&sprite_states,
			&camera,
			&sys,
			&current_filter
		](
			sge::renderer::context::ffp &_context,
			sge::camera::projection_matrix const &_projection
		)
		{
			sge::renderer::state::ffp::transform::object_unique_ptr const projection_state(
				sys.renderer_device_ffp().create_transform_state(
					sge::renderer::state::ffp::transform::parameters(
						_projection.get()
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

			{
				sge::renderer::state::ffp::transform::scoped const projection_transform(
					_context,
					sge::renderer::state::ffp::transform::mode::projection,
					*projection_state
				);

				sge::renderer::state::ffp::transform::scoped const world_transform(
					_context,
					sge::renderer::state::ffp::transform::mode::world,
					*world_state
				);

				sge::renderer::state::core::sampler::scoped_single const scoped_filter(
					_context,
					sge::renderer::texture::stage(
						0u
					),
					current_filter.get().second.get()
				);

				sge::sprite::render::range_with_options(
					sge::sprite::render::parameters<
						sprite_state_choices
					>(
						_context,
						sprite_buffers.parameters().vertex_declaration()
					),
					sprite_range,
					sprite_states,
					sge::sprite::state::default_options<
						sprite_state_choices
					>()
				);
			}

			sge::font::vector const font_pos(
				fcppt::math::vector::null<
					sge::font::vector
				>()
			);

			sge::font::align_h::max_width const font_width(
				fcppt::cast::size<
					sge::font::unit
				>(
					fcppt::cast::to_signed(
						sge::renderer::target::viewport_size(
							sys.renderer_device_core().onscreen_target()
						).w()
					)
				)
			);

			sge::font::draw::simple(
				sys.renderer_device_ffp(),
				_context,
				*font,
				current_filter.get().first
				+
				text_appendix,
				sge::font::text_parameters(
					sge::font::align_h::variant(
						sge::font::align_h::left(
							font_width
						)
					)
				),
				font_pos,
				sge::image::color::any::object{
					sge::image::color::predef::red()
				},
				sge::renderer::texture::emulate_srgb::yes
			);

			sge::font::draw::simple(
				sys.renderer_device_ffp(),
				_context,
				*font,
				sge::font::from_fcppt_string(
					frames_counter.frames_str()
				)
				+
				SGE_FONT_LIT(" fps"),
				sge::font::text_parameters(
					sge::font::align_h::variant(
						sge::font::align_h::right(
							font_width
						)
					)
				),
				font_pos,
				sge::image::color::any::object{
					sge::image::color::predef::red()
				},
				sge::renderer::texture::emulate_srgb::yes
			);
		}
	);

	auto const draw(
		[
			&frame_timer,
			&frames_counter,
			&draw_camera,
			&camera,
			&sys
		]{
			if(
				sge::renderer::target::viewport_is_null(
					sys.renderer_device_core().onscreen_target().viewport()
				)
			)
				return;

			camera.update(
				std::chrono::duration_cast<
					sge::camera::update_duration
				>(
					sge::timer::elapsed_and_reset(
						frame_timer
					)
				)
			);

			frames_counter.update();

			sge::renderer::context::scoped_ffp const scoped_block(
				sys.renderer_device_ffp(),
				sys.renderer_device_ffp().onscreen_target()
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::lightblue()
					}
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

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&sys,
					&camera,
					&key_event,
					&draw
				](
					awl::event::base const &_event
				)
				{
					sge::systems::quit_on_escape(
						sys,
						_event
					);

					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							sge::input::keyboard::event::key const
						>(
							_event
						),
						[
							&key_event
						](
							fcppt::reference<
								sge::input::keyboard::event::key const
							> const _key_event
						)
						{
							key_event(
								_key_event.get()
							);
						}
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
							&camera,
							&draw
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
									>
								)
								{
									draw();
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
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
