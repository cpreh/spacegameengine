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


#include <sge/camera/activation_state.hpp>
#include <sge/camera/identity_gizmo.hpp>
#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/projection/perspective.hpp>
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
#include <sge/font/text/lit.hpp>
#include <sge/font/text/part.hpp>
#include <sge/font/text/string.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/store.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/gray8.hpp>
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
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/depth_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/stencil_buffer.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/window_mode.hpp>
#include <sge/renderer/window_parameters.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/filter/anisotropic.hpp>
#include <sge/renderer/texture/filter/anisotropy_type.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/filter/mipmap.hpp>
#include <sge/renderer/texture/filter/object.hpp>
#include <sge/renderer/texture/filter/point.hpp>
#include <sge/renderer/texture/filter/trilinear.hpp>
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
#include <sge/systems/viewport/center_on_resize.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/time/second.hpp>
#include <sge/time/timer.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/make_shared_ptr.hpp>
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
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <utility>
#include <cstdlib>

namespace
{

sge::texture::const_part_ptr const
make_texture(
	sge::renderer::device_ptr const _device,
	sge::image2d::view::const_object const &_view,
	sge::renderer::texture::filter::object const &_filter
)
{
	return
		fcppt::make_shared_ptr<
			sge::texture::part_raw
		>(
			sge::renderer::texture::create_planar_from_view(
				_device,
				_view,
				_filter,
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::repeat
				),
				sge::renderer::resource_flags::none
			)
		);
}

template<
	typename Sprite,
	typename Textures
>
void
change_texture(
	sge::input::keyboard::key_event const &_event,
	Sprite &_sprite,
	sge::font::text::string &_text,
	Textures const &_textures
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
	
	typename Textures::size_type const index(
		digit->get() - 1u
	);

	if(
		index
		>= _textures.size()
	)
		return;

	typename Textures::const_reference ref(
		_textures[
			index
		]
	);

	_text = ref.first;

	_sprite.texture(
		ref.second
	);
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
				sge::renderer::window_parameters(
					FCPPT_TEXT("sge texture filter example")
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::display_mode(
						sge::renderer::screen_size(
							1024,
							768
						),
						sge::renderer::bit_depth::depth32,
						sge::renderer::refresh_rate_dont_care
					),
					sge::renderer::depth_buffer::off,
					sge::renderer::stencil_buffer::off,
					sge::renderer::window_mode::windowed,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::systems::viewport::center_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				| sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::confine
				)
				| sge::systems::cursor_option::hide
			)
		)
		(
			sge::systems::parameterless::font
		)
	);

	sge::camera::object camera(
		sge::camera::parameters(
			sge::camera::projection::perspective(
				sge::renderer::aspect(
					sys.renderer()->screen_size()
				),
				// fov
				fcppt::math::deg_to_rad(
					static_cast<
						sge::renderer::scalar
					>(
						90
					)
				),
				// near
				static_cast<
					sge::renderer::scalar
				>(
					0.1
				),
				// far
				static_cast<
					sge::renderer::scalar
				>(
					100
				)
			),
			// movementspeed
			static_cast<
				sge::renderer::scalar
			>(
				2.0
			),
			// mousespeed
			static_cast<
				sge::renderer::scalar
			>(
				200.0
			),
			// position
			sge::camera::identity_gizmo(),
			*sys.keyboard_collector(),
			*sys.mouse_collector(),
			sge::camera::activation_state::active
		)
	);

	sge::image2d::dim const block_size(
		16u,
		16u
	);

	sge::image::size_type const num_blocks(
		16u
	);

	typedef sge::image2d::gray8 store_type;

	store_type whole_store(
		block_size * num_blocks
	);

	{
		store_type white_store(
			block_size
		);

		sge::image2d::algorithm::fill(
			white_store.view(),
			sge::image::colors::white()
		);

		store_type black_store(
			block_size
		);

		sge::image2d::algorithm::fill(
			black_store.view(),
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
						(((x + y) % 2u) == 0u)
						?
							white_store.view()
						:
							black_store.view()
					),
					sge::image2d::view::sub(
						sge::image2d::view::object(
							whole_store.view()
						),
						sge::image2d::rect(
							sge::image2d::rect::vector(
								x * block_size.w(),
								y * block_size.h()
							),
							block_size
						)
					)
				);
	}

	typedef std::pair<
		sge::font::text::string,
		sge::texture::const_part_ptr
	> string_texture_pair;

	typedef fcppt::container::array<
		string_texture_pair,
		5u
	> texture_array;

	sge::image2d::view::const_object const texture_view(
		sge::image2d::view::to_const(
			whole_store.view()
		)
	);

	sge::renderer::texture::filter::anisotropy_type const anisotropy(
		sys.renderer()->caps().max_anisotropy()
	);

	texture_array const textures =
	{{
		std::make_pair(
			SGE_FONT_TEXT_LIT("point"),
			make_texture(
				sys.renderer(),
				texture_view,
				sge::renderer::texture::filter::point
			)
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("linear"),
			make_texture(
				sys.renderer(),
				texture_view,
				sge::renderer::texture::filter::linear
			)
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("mipmap"),
			make_texture(
				sys.renderer(),
				texture_view,
				sge::renderer::texture::filter::mipmap
			)
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("trilinear"),
			make_texture(
				sys.renderer(),
				texture_view,
				sge::renderer::texture::filter::trilinear
			)
		),
		std::make_pair(
			SGE_FONT_TEXT_LIT("anisotropic ")
			+ fcppt::lexical_cast<
				sge::font::text::string
			>(
				anisotropy
			)
			+ SGE_FONT_TEXT_LIT('x'),
			make_texture(
				sys.renderer(),
				texture_view,
				sge::renderer::texture::filter::anisotropic(
					anisotropy
				)
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
		1000
	);

	sprite_object sprite(
		sprite_parameters()
		.pos(
			sprite_object::point(
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
			100u
		)
		.texture(
			sge::texture::const_part_ptr()
		)
		.elements()
	);

	sge::font::text::string current_text(
		SGE_FONT_TEXT_LIT("Press 1 through ")
		+
		fcppt::lexical_cast<
			sge::font::text::string
		>(
			textures.size()
		)
		+ SGE_FONT_TEXT_LIT(" to select a filter!")
	);

	bool running(
		true
	);

	fcppt::signal::scoped_connection const input_connection(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	fcppt::signal::scoped_connection const texture_connection(
		sys.keyboard_collector()->key_callback(
			std::tr1::bind(
				change_texture<
					sprite_object,
					texture_array
				>,
				std::tr1::placeholders::_1,
				std::tr1::ref(
					sprite
				),
				std::tr1::ref(
					current_text
				),
				textures
			)
		)
	);

	sge::font::metrics_ptr const font_metrics(
		sys.font_system()->create_font(
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

	sge::time::timer frame_timer(
		sge::time::second(
			1
		)
	);

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(
				sge::renderer::state::color::clear_color
					= sge::image::colors::lightblue()
			)
	);

	while(
		running
	)
	{
		sys.window()->dispatch();

		camera.update(
			static_cast<
				sge::renderer::scalar
			>(
				frame_timer.reset()
			)
		);

		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		sys.renderer()->transform(
			sge::renderer::matrix_mode::world,
			camera.world()
		);

		sys.renderer()->transform(
			sge::renderer::matrix_mode::projection,
			camera.projection()
		);

		sge::sprite::render_one_advanced(
			sprite_sys,
			sprite
		);

		sge::font::text::draw(
			font_metrics,
			font_drawer,
			current_text,
			sge::font::rect(
				sge::font::rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::font::rect::dim
				>(
					sys.renderer()->screen_size()	
				)
			),
			sge::font::text::align_h::left,
			sge::font::text::align_v::top,
			sge::font::text::flags::none
		);
	}
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr
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
