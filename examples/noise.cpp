//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/channel8.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/store/l8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/noise/sample.hpp>
#include <sge/noise/sample_parameters.hpp>
#include <sge/noise/perlin/object.hpp>
#include <sge/noise/simplex/object.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
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
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
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
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part_raw_ref.hpp>
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
#include <awl/main/function_context.hpp>
#include <mizuiro/color/channel/luminance.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/interpolation/perlin_fifth_degree.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <metal.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


namespace
{

struct interpolator
{
	template<
		typename Float,
		typename Value
	>
	Value
	operator()(
		Float const _f,
		Value const _v1,
		Value const _v2
	) const
	{
		return
			fcppt::math::interpolation::perlin_fifth_degree(
				_f,
				_v1,
				_v2
			);
	}
};

void
fill_texture(
	sge::image2d::store::l8::view_type _view
)
{
	using
	dim_type
	=
	sge::image2d::store::l8::view_type::dim;

	using
	dim_value_type
	=
	dim_type::value_type;

	/*
	typedef
	sge::noise::simplex::object<double,2>
	noise_type;
	*/
	using
	noise_type
	=
	sge::noise::perlin::object<
		double,
		2,
		interpolator
	>;

	using
	param_type
	=
	sge::noise::sample_parameters<
		noise_type
	>;

	fcppt::random::generator::minstd_rand rng(
		fcppt::random::generator::seed_from_chrono<fcppt::random::generator::minstd_rand::seed>());

	/*
	noise_type noise_generator(
		sge::noise::simplex::width(
			128u));
			*/
	noise_type noise_generator(
		noise_type::dim(
			_view.size()[0]/100, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			_view.size()[1]/100), // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		fcppt::make_ref(
			rng
		)
	);

	// TODO(philipp): Refactor this
	for (dim_value_type y = 0; y < _view.size()[1]; ++y)
	{
		for (dim_value_type x = 0; x < _view.size()[0]; ++x)
		{
			_view[
				sge::image2d::store::l8::view_type::dim(
					x,
					y
				)
			].set(
				mizuiro::color::channel::luminance(),
				static_cast<sge::image::channel8>(
					256.0 * // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
					(
						0.5 + 0.5 * // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						sge::noise::sample(
							fcppt::make_ref(
								noise_generator
							),
							param_type(
								param_type::position_type(
									noise_type::vector_type(
										static_cast<noise_type::value_type>(
											x),
										static_cast<noise_type::value_type>(
											y))),
								param_type::amplitude_type(
									0.8 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
								),
								param_type::frequency_type(
									.005 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
								),
								param_type::octaves_type(
									6U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
								)
							)
						)
					)
				)
			);
		}
	}
}

}

awl::main::exit_code
example_main(
	awl::main::function_context const &
)
try
{
	using
	noise_type
	=
	sge::noise::simplex::object<
		double,
		2
	>;

	noise_type noise_generator(
		sge::noise::simplex::width(
			128U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		)
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("raw noise generator spit out: ")
		<< noise_generator.sample(
			noise_type::vector_type(
				23.0, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				42.0 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		)
		<< FCPPT_TEXT('\n');

	sge::systems::instance<
		sge::systems::with_window,
		sge::systems::with_renderer<
			sge::systems::renderer_caps::ffp
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("noisetest")
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
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::log::option_container{
						sge::log::option{
							sge::log::location(),
							fcppt::log::level::debug
						}
					}
				)
			)
		)
	);

	using
	sprite_choices
	=
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
			sge::sprite::config::texture_size_option::always
		>,
		metal::list<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1U
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::shared
			>
		>
	>;

	using
	sprite_buffers_type
	=
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	>;

	using
	sprite_object
	=
	sge::sprite::object<
		sprite_choices
	>;

	sprite_buffers_type sprite_buffers(
		fcppt::make_ref(
			sys.renderer_device_core()
		),
		sge::sprite::buffers::option::dynamic);

	using
	sprite_state_choices
	=
	sge::sprite::state::all_choices;

	using
	sprite_state_object
	=
	sge::sprite::state::object<
		sprite_state_choices
	>;

	using
	sprite_state_parameters
	=
	sge::sprite::state::parameters<
		sprite_state_choices
	>;

	sprite_state_object sprite_state(
		fcppt::make_ref(
			sys.renderer_device_ffp()
		),
		sprite_state_parameters()
	);

	using
	store_type
	=
	sge::image2d::store::l8;

	store_type const store{
		fcppt::math::dim::fill<
			sge::image2d::dim
		>(
			1024
		),
		store_type::init_function{
			&fill_texture
		}
	};

	sge::renderer::texture::planar_unique_ptr const noise_texture(
		sge::renderer::texture::create_planar_from_view(
			fcppt::make_ref(
				sys.renderer_device_core()
			),
			sge::image2d::view::const_object(
				store.const_wrapped_view()
			),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::no
		)
	);

	sprite_object const spr(
		sge::sprite::roles::pos{} =
			fcppt::math::vector::null<
				sprite_object::vector
			>(),
		sge::sprite::roles::texture0{} =
			sprite_object::texture_type{
				fcppt::make_shared_ptr<
					sge::texture::part_raw_ref
				>(
					*noise_texture
				)
			}
	);

	auto const draw(
		[
			&spr,
			&sprite_buffers,
			&sprite_state,
			&sys
		]{
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
			);

			sge::sprite::process::one(
				scoped_block.get(),
				spr,
				sprite_buffers,
				sprite_state
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&draw
				](
					awl::event::base const &_event
				)
				{
					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							sge::renderer::event::render const
						>(
							_event
						),
						[
							&draw
						](
							fcppt::reference<
								sge::renderer::event::render const
							>
						)
						{
							draw();
						}
					);
				}
			}
		);
//! [running_block]
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
