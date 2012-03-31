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
#include <sge/config/media_path.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/size_type.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text/align_h.hpp>
#include <sge/font/text/align_v.hpp>
#include <sge/font/text/draw.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/string.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/store.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/l8.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code_to_digit.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/optional_digit.hpp>
#include <sge/renderer/active_target.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/target_base.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/caps/object.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/filter/mipmap.hpp>
#include <sge/renderer/texture/filter/object.hpp>
#include <sge/renderer/texture/filter/point.hpp>
#include <sge/renderer/texture/filter/scoped.hpp>
#include <sge/renderer/texture/filter/trilinear.hpp>
#include <sge/renderer/texture/filter/anisotropic/level.hpp>
#include <sge/renderer/texture/filter/anisotropic/make.hpp>
#include <sge/renderer/texture/filter/anisotropic/mip.hpp>
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
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/geometry/update_one.hpp>
#include <sge/sprite/render/matrix_options.hpp>
#include <sge/sprite/render/options.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/texture/part_raw.hpp>
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
#include <fcppt/exception.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/object_impl.hpp>
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
	sge::font::text::string,
	sge::renderer::texture::filter::object
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

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance const sys(
		sge::systems::list()
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
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				| sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive
				)
			)
		)
		(
			sge::systems::font()
		)
	);

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::first_person::is_active(
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
			sge::image::colors::white()
		);

		store_type black_store(
			block_size
		);

		sge::image2d::algorithm::fill(
			sge::image2d::view::object(
				black_store.wrapped_view()
			),
			sge::image::colors::black()
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
				sge::image2d::algorithm::copy_and_convert(
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

	sge::renderer::texture::filter::anisotropic::level const anisotropy(
		sys.renderer().caps().max_anisotropy().get()
	);

	sge::font::text::string const anisotropy_string(
		SGE_FONT_TEXT_LIT(' ')
		+
		fcppt::insert_to_string<
			sge::font::text::string
		>(
			anisotropy
		)
		+
		SGE_FONT_TEXT_LIT('x')
	);

	filter_array const filters =
	{{
		std::make_pair(
			SGE_FONT_TEXT_LIT("point"),
			sge::renderer::texture::filter::point()
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("linear"),
			sge::renderer::texture::filter::linear()
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("mipmap"),
			sge::renderer::texture::filter::mipmap()
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("trilinear"),
			sge::renderer::texture::filter::trilinear()
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("anisotropic")
			+
			anisotropy_string,
			sge::renderer::texture::filter::anisotropic::make(
				sge::renderer::texture::filter::anisotropic::mip::off,
				anisotropy
			)
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("anisotropic")
			+
			anisotropy_string
			+
			SGE_FONT_TEXT_LIT(" + mipmap"),
			sge::renderer::texture::filter::anisotropic::make(
				sge::renderer::texture::filter::anisotropic::mip::point,
				anisotropy
			)
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("anisotropic")
			+
			anisotropy_string
			+
			SGE_FONT_TEXT_LIT(" + trilinear"),
			sge::renderer::texture::filter::anisotropic::make(
				sge::renderer::texture::filter::anisotropic::mip::linear,
				anisotropy
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
				sge::sprite::config::texture_coordinates::repetition
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

	sprite_buffers_type sprite_buffers(
		sys.renderer(),
		sge::sprite::buffers::option::static_
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
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				sge::renderer::texture::create_planar_from_view(
					sys.renderer(),
					sge::image2d::view::to_const(
						sge::image2d::view::object(
							whole_store.wrapped_view()
						)
					),
					sge::renderer::texture::mipmap::all_levels(
						sge::renderer::texture::mipmap::auto_generate::yes
					),
					sge::renderer::resource_flags::none
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
		sys.renderer(),
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

	sge::font::metrics_ptr const font_metrics(
		sys.font_system().create_font(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("default.ttf"),
			static_cast<
				sge::font::size_type
			>(
				30
			)
		)
	);

	sge::font::text::drawer_3d font_drawer(
		sys.renderer(),
		sge::image::colors::red()
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

	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(
				sge::renderer::state::color::back_buffer_clear_color
					= sge::image::colors::lightblue()
			)
	);

	sge::timer::frames_counter frames_counter;

	sge::font::text::string const text_appendix(
		SGE_FONT_TEXT_LIT(" (Press 1 through ")
		+
		fcppt::insert_to_string<
			sge::font::text::string
		>(
			filters.size()
		)
		+ SGE_FONT_TEXT_LIT(" to select a filter!)")
	);

	while(
		sys.window_system().poll()
	)
	{
		camera.update(
			sge::timer::elapsed_and_reset<
				sge::camera::update_duration
			>(
				frame_timer
			)
		);

		frames_counter.update();

		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		sys.renderer().transform(
			sge::renderer::matrix_mode::world,
			sge::camera::matrix_conversion::world(
				camera.coordinate_system()
			)
		);

		sys.renderer().transform(
			sge::renderer::matrix_mode::projection,
			camera.projection_matrix().get()
		);

		{
			sge::renderer::texture::filter::scoped const scoped_filter(
				sys.renderer(),
				sge::renderer::texture::stage(
					0u
				),
				current_filter->second
			);

			sge::sprite::render::range_with_options<
				sge::sprite::render::options<
					sge::sprite::render::matrix_options::nothing,
					sge::sprite::render::state_options::nothing,
					sge::sprite::render::vertex_options::declaration_and_buffer
				>
			>(
				sprite_buffers.parameters(),
				sprite_range
			);
		}

		sge::font::text::draw(
			*font_metrics,
			font_drawer,
			current_filter->first
			+
			text_appendix,
			sge::font::rect(
				sge::font::rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::font::rect::dim
				>(
					sge::renderer::active_target(
						sys.renderer()
					).viewport().get().size()
				)
			),
			sge::font::text::align_h::left,
			sge::font::text::align_v::top,
			sge::font::text::flags::none
		);

		sge::font::text::draw(
			*font_metrics,
			font_drawer,
			sge::font::text::from_fcppt_string(
				frames_counter.frames_str()
			)
			+ SGE_FONT_TEXT_LIT(" fps"),
			sge::font::rect(
				sge::font::rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::font::rect::dim
				>(
					sge::renderer::active_target(
						sys.renderer()
					).viewport().get().size()
				)
			),
			sge::font::text::align_h::right,
			sge::font::text::align_v::top,
			sge::font::text::flags::none
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
