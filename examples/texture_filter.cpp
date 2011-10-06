/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/rotation_speed.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/projection/update_perspective_from_viewport.hpp>
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
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_code_to_digit.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/optional_digit.hpp>
#include <sge/renderer/active_target.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/target_base.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/filter/anisotropic/level.hpp>
#include <sge/renderer/texture/filter/anisotropic/make.hpp>
#include <sge/renderer/texture/filter/anisotropic/mip.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/filter/mipmap.hpp>
#include <sge/renderer/texture/filter/object.hpp>
#include <sge/renderer/texture/filter/point.hpp>
#include <sge/renderer/texture/filter/scoped.hpp>
#include <sge/renderer/texture/filter/trilinear.hpp>
#include <sge/renderer/texture/mipmap/all_levels.hpp>
#include <sge/renderer/texture/mipmap/auto_generate.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/render_one_advanced.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_repetition.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/frames_counter.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>
#include <cstdlib>
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

}

int
main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge texture filter example"),
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
			sge::systems::parameterless::font
		)
	);

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sge::camera::first_person::movement_speed(
				4.0f
			),
			sge::camera::first_person::rotation_speed(
				200.0f
			),
			sys.keyboard_collector(),
			sys.mouse_collector()
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
		sys.renderer().caps().max_anisotropy()
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

	typedef sge::sprite::choices<
		sge::sprite::type_choices<
			int,
			float,
			sge::sprite::no_color
		>,
		boost::mpl::vector3<
			sge::sprite::with_dim,
			sge::sprite::with_texture,
			sge::sprite::with_repetition
		>
	> sprite_choices;

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sge::sprite::object<
		sprite_choices
	> sprite_object;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_system sprite_sys(
		sys.renderer()
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

	sprite_object sprite(
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
					sge::renderer::texture::address_mode2(
						sge::renderer::texture::address_mode::repeat
					),
					sge::renderer::resource_flags::none
				)
			)
		)
		.elements()
	);

	bool running(
		true
	);

	fcppt::signal::scoped_connection const input_connection(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	filter_array::const_pointer current_filter(
		filters.data()
	);

	fcppt::signal::scoped_connection const texture_connection(
		sys.keyboard_collector().key_callback(
			std::tr1::bind(
				::change_filter,
				std::tr1::placeholders::_1,
				filters,
				fcppt::ref(
					current_filter
				)
			)
		)
	);

	fcppt::signal::scoped_connection const viewport_connection(
		sys.viewport_manager().manage_callback(
			std::tr1::bind(
				sge::camera::projection::update_perspective_from_viewport,
				fcppt::ref(
					sys.renderer()
				),
				fcppt::ref(
					camera
				),
				sge::renderer::projection::fov(
					fcppt::math::deg_to_rad(
						90.f
					)
				),
				sge::renderer::projection::near(
					0.1f
				),
				sge::renderer::projection::far(
					1000.f
				)
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

	sge::timer::basic<sge::timer::clocks::standard> frame_timer(
		sge::timer::parameters<sge::timer::clocks::standard>(
			sge::camera::duration(
				1.0f)));

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
		running
	)
	{
		sys.window().dispatch();

		camera.update(
			sge::timer::elapsed_and_reset<
				sge::camera::duration
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
			camera.world()
		);

		sys.renderer().transform(
			sge::renderer::matrix_mode::projection,
			camera.projection()
		);

		{
			sge::renderer::texture::filter::scoped const scoped_filter(
				sys.renderer(),
				sge::renderer::stage(0u),
				current_filter->second
			);

			sge::sprite::render_one_advanced(
				sprite_sys,
				sprite
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
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
