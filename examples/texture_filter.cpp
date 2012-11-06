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


#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_scoped_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/string.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/store.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/l8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/l8.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/algorithm/copy.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code_to_digit.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/optional_digit.hpp>
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
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/object_scoped_ptr.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/scoped_single.hpp>
#include <sge/renderer/state/core/sampler/address/default.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/linear.hpp>
#include <sge/renderer/state/core/sampler/filter/mipmap.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/point.hpp>
#include <sge/renderer/state/core/sampler/filter/trilinear.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/level.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_scoped_ptr.hpp>
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
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/geometry/update_one.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/state/choices.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/mouse_collector.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_charconv.hpp>
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/frames_counter.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/reference_wrapper.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_map.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef std::pair<
	sge::font::string,
	sge::renderer::state::core::sampler::const_object_ref
> string_filter_pair;

typedef fcppt::container::array<
	string_filter_pair,
	7u
> filter_array;

void
change_filter(
	sge::input::keyboard::key_event const &_event,
	filter_array const &_filters,
	filter_array::const_pointer &_result
)
{
	if(
		!_event.pressed()
	)
		return;

	sge::input::keyboard::optional_digit const digit(
		sge::input::keyboard::key_code_to_digit(
			_event.key_code()
		)
	);

	if(
		!digit
	)
		return;

	filter_array::size_type const index(
		digit->get() - 1u
	);

	if(
		index
		>= _filters.size()
	)
		return;

	_result =
		&_filters[
			index
		];
}

class change_filter_functor
{
	FCPPT_NONASSIGNABLE(
		change_filter_functor
	);
public:
	change_filter_functor(
		filter_array const &_filters,
		filter_array::const_pointer &_result
	)
	:
		filters_(
			_filters
		),
		result_(
			_result
		)
	{
	}

	void
	operator()(
		sge::input::keyboard::key_event const &_event
	) const
	{
		change_filter(
			_event,
			filters_,
			result_
		);
	}
private:
	filter_array const &filters_;

	filter_array::const_pointer &result_;
};

sge::renderer::state::core::sampler::parameters const
make_sampler_parameters(
	sge::renderer::state::core::sampler::filter::parameters const &_filter
)
{
	return
		sge::renderer::state::core::sampler::parameters(
			sge::renderer::state::core::sampler::address::default_(),
			_filter
		);
}

sge::renderer::state::core::sampler::parameters const
make_anisotropic_sampler_parameters(
	sge::renderer::state::core::sampler::filter::anisotropic::mip::type const _mip,
	sge::renderer::state::core::sampler::filter::anisotropic::level const _level
)
{
	return
		make_sampler_parameters(
			sge::renderer::state::core::sampler::filter::parameters(
				sge::renderer::state::core::sampler::filter::anisotropic::parameters(
					_mip,
					_level
				)
			)
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
		boost::mpl::vector5<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector2<
					sge::systems::keyboard_collector,
					sge::systems::mouse_collector
				>
			>,
			sge::systems::with_charconv,
			sge::systems::with_font
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge texture filter example")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive
				)
			)
		)
	);

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::is_active(
				true
			),
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
		block_element_size,
		block_element_size
	);

	sge::image::size_type const num_blocks(
		2u
	);

	typedef sge::image2d::l8 store_type;

	store_type whole_store(
		block_size * num_blocks
	);

	{
		store_type white_store(
			block_size
		);

		sge::image2d::algorithm::fill(
			sge::image2d::view::object(
				white_store.wrapped_view()
			),
			sge::image::color::any::object(
				sge::image::color::l8(
					sge::image::color::init::luminance() %= 1.
				)
			)
		);

		store_type black_store(
			block_size
		);

		sge::image2d::algorithm::fill(
			sge::image2d::view::object(
				black_store.wrapped_view()
			),
			sge::image::color::any::object(
				sge::image::color::l8(
					sge::image::color::init::luminance() %= 0.
				)
			)
		);

		for(
			sge::image::size_type y = 0;
			y < num_blocks;
			++y
		)
			for(
				sge::image::size_type x = 0;
				x < num_blocks;
				++x
			)
				sge::image2d::algorithm::copy(
					sge::image2d::view::to_const(
						sge::image2d::view::object(
							(((x + y) % 2u) == 0u)
							?
								white_store.wrapped_view()
							:
								black_store.wrapped_view()
						)
					),
					sge::image2d::view::sub(
						sge::image2d::view::object(
							whole_store.wrapped_view()
						),
						sge::image2d::rect(
							sge::image2d::rect::vector(
								x * block_size.w(),
								y * block_size.h()
							),
							block_size
						)
					),
					sge::image::algorithm::may_overlap::no
				);
	}

	sge::renderer::state::core::sampler::filter::anisotropic::level const anisotropy(
		sys.renderer_core().caps().max_anisotropy().get()
	);

	sge::font::string const anisotropy_string(
		SGE_FONT_LIT(' ')
		+
		fcppt::insert_to_string<
			sge::font::string
		>(
			anisotropy
		)
		+
		SGE_FONT_LIT('x')
	);

	sge::renderer::state::core::sampler::object_scoped_ptr const
		point_sampler(
			sys.renderer_core().create_sampler_state(
				make_sampler_parameters(
					sge::renderer::state::core::sampler::filter::point()
				)
			)
		),
		linear_sampler(
			sys.renderer_core().create_sampler_state(
				make_sampler_parameters(
					sge::renderer::state::core::sampler::filter::linear()
				)
			)
		),
		mipmap_sampler(
			sys.renderer_core().create_sampler_state(
				make_sampler_parameters(
					sge::renderer::state::core::sampler::filter::mipmap()
				)
			)
		),
		trilinear_sampler(
			sys.renderer_core().create_sampler_state(
				make_sampler_parameters(
					sge::renderer::state::core::sampler::filter::trilinear()
				)
			)
		),
		anisotropic_sampler(
			sys.renderer_core().create_sampler_state(
				make_anisotropic_sampler_parameters(
					sge::renderer::state::core::sampler::filter::anisotropic::mip::off,
					anisotropy
				)
			)
		),
		anisotropic_mipmap_sampler(
			sys.renderer_core().create_sampler_state(
				make_anisotropic_sampler_parameters(
					sge::renderer::state::core::sampler::filter::anisotropic::mip::point,
					anisotropy
				)
			)
		),
		anisotropic_trilinear_sampler(
			sys.renderer_core().create_sampler_state(
				make_anisotropic_sampler_parameters(
					sge::renderer::state::core::sampler::filter::anisotropic::mip::linear,
					anisotropy
				)
			)
		);

	filter_array const filters =
	{{
		std::make_pair(
			SGE_FONT_LIT("point"),
			fcppt::cref(
				*point_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("linear"),
			fcppt::cref(
				*linear_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("mipmap"),
			fcppt::cref(
				*mipmap_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("trilinear"),
			fcppt::cref(
				*trilinear_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("anisotropic")
			+
			anisotropy_string,
			fcppt::cref(
				*anisotropic_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("anisotropic")
			+
			anisotropy_string
			+
			SGE_FONT_LIT(" + mipmap"),
			fcppt::cref(
				*anisotropic_mipmap_sampler
			)
		),
		std::make_pair(
			SGE_FONT_LIT("anisotropic")
			+
			anisotropy_string
			+
			SGE_FONT_LIT(" + trilinear"),
			fcppt::cref(
				*anisotropic_trilinear_sampler
			)
		)
	}};

	typedef sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				int
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::normal_size,
		boost::mpl::vector1<
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::repetition,
				sge::sprite::config::texture_ownership::shared
			>
		>
	> sprite_choices;

	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	> sprite_buffers_type;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	typedef sge::sprite::state::choices<
		boost::mpl::vector0<>
	> sprite_state_choices;

	typedef sge::sprite::state::object<
		sprite_state_choices
	> sprite_state_object;

	typedef sge::sprite::state::parameters<
		sprite_state_choices
	> sprite_state_parameters;

	sprite_buffers_type sprite_buffers(
		sys.renderer_core(),
		sge::sprite::buffers::option::static_
	);

	sprite_state_object sprite_states(
		sys.renderer_ffp(),
		sprite_state_parameters()
	);

	sprite_object::unit const sprite_size(
		2000
	);

	sprite_object::repetition_type::value_type const repetition(
		static_cast<
			sprite_object::repetition_type::value_type
		>(
			sprite_size / 5
		)
	);

	sprite_object const sprite(
		sprite_parameters()
		.pos(
			sprite_object::vector(
				-(sprite_size / 2),
				-(sprite_size / 2)
			)
		)
		.size(
			sprite_object::dim(
				sprite_size,
				sprite_size
			)
		)
		.repetition(
			sprite_object::repetition_type(
				repetition,
				repetition
			)
		)
		.texture(
			sge::texture::const_part_shared_ptr(
				fcppt::make_unique_ptr<
					sge::texture::part_raw_ptr
				>(
					sge::renderer::texture::create_planar_from_view(
						sys.renderer_core(),
						sge::image2d::view::to_const(
							sge::image2d::view::object(
								whole_store.wrapped_view()
							)
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
	);

	typedef sge::sprite::render::range<
		sprite_choices
	> sprite_range_type;

	sprite_range_type const sprite_range(
		sge::sprite::geometry::update_one(
			sprite,
			sprite_buffers
		)
	);

	fcppt::signal::scoped_connection const input_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	filter_array::const_pointer current_filter(
		filters.data()
	);

	fcppt::signal::scoped_connection const texture_connection(
		sys.keyboard_collector().key_callback(
			change_filter_functor(
				filters,
				current_filter
			)
		)
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
			sge::camera::update_duration(
				1.0f
			)
		)
	);

	sge::timer::frames_counter frames_counter;

	sge::font::string const text_appendix(
		SGE_FONT_LIT(" (Press 1 through ")
		+
		fcppt::insert_to_string<
			sge::font::string
		>(
			filters.size()
		)
		+ SGE_FONT_LIT(" to select a filter!)")
	);

	sge::font::object_scoped_ptr const font(
		sys.font_system().create_font(
			sge::font::parameters()
				.family(
					FCPPT_TEXT("sans")
				)
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		if(
			sge::renderer::target::viewport_is_null(
				sys.renderer_core().onscreen_target().viewport()
			)
		)
			continue;

		camera.update(
			sge::timer::elapsed_and_reset<
				sge::camera::update_duration
			>(
				frame_timer
			)
		);

		frames_counter.update();

		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_ffp(),
			sys.renderer_ffp().onscreen_target()
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::lightblue()
			)
		);

		sge::renderer::state::ffp::transform::object_scoped_ptr const projection_state(
			sys.renderer_ffp().create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					camera.projection_matrix().get()
				)
			)
		);

		sge::renderer::state::ffp::transform::object_scoped_ptr const world_state(
			sys.renderer_ffp().create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					sge::camera::matrix_conversion::world(
						camera.coordinate_system()
					)
				)
			)
		);

		{
			sge::renderer::state::ffp::transform::scoped const projection_transform(
				scoped_block.get(),
				sge::renderer::state::ffp::transform::mode::projection,
				*projection_state
			);

			sge::renderer::state::ffp::transform::scoped const world_transform(
				scoped_block.get(),
				sge::renderer::state::ffp::transform::mode::world,
				*world_state
			);

			sge::renderer::state::core::sampler::scoped_single const scoped_filter(
				scoped_block.get(),
				sge::renderer::texture::stage(
					0u
				),
				current_filter->second.get()
			);

			sge::sprite::render::range_with_options(
				sge::sprite::render::parameters<
					sprite_state_choices
				>(
					scoped_block.get(),
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
			sge::font::vector::null()
		);

		sge::font::unit const font_width(
			static_cast<
				sge::font::unit
			>(
				sge::renderer::target::viewport_size(
					sys.renderer_core().onscreen_target()
				).w()
			)
		);

		sge::font::draw::simple(
			sys.renderer_ffp(),
			scoped_block.get(),
			*font,
			current_filter->first
			+
			text_appendix,
			sge::font::text_parameters(
				sge::font::align_h::left
			)
			.max_width(
				font_width
			),
			font_pos,
			sge::image::colors::red(),
			sge::renderer::texture::emulate_srgb::yes
		);

		sge::font::draw::simple(
			sys.renderer_ffp(),
			scoped_block.get(),
			*font,
			sge::font::from_fcppt_string(
				frames_counter.frames_str()
			)
			+ SGE_FONT_LIT(" fps"),
			sge::font::text_parameters(
				sge::font::align_h::right
			)
			.max_width(
				font_width
			),
			font_pos,
			sge::image::colors::red(),
			sge::renderer::texture::emulate_srgb::yes
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
