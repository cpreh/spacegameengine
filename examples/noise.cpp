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

#include <sge/image/colors.hpp>
#include <sge/image/store.hpp>
#include <sge/image/color/channel8.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/l8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/log/global.hpp>
#include <sge/noise/sample.hpp>
#include <sge/noise/sample_parameters.hpp>
#include <sge/noise/simplex/object.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/windowed.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/default_parameters.hpp>
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
#include <sge/sprite/defaults/defaults.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <mizuiro/color/channel/luminance.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <fcppt/config/external_end.hpp>

namespace
{

void
fill_texture(
	sge::image2d::l8::view_type _view)
{
	typedef sge::image2d::l8::view_type::dim dim_type;
	typedef dim_type::value_type dim_value_type;

	typedef
	sge::noise::simplex::object<double,2>
	noise_type;

	typedef
	sge::noise::sample_parameters<noise_type>
	param_type;

	noise_type noise_generator(
		sge::noise::simplex::width(
			128u));

	for (dim_value_type y = 0; y < _view.size()[1]; ++y)
		for (dim_value_type x = 0; x < _view.size()[0]; ++x)
		{
			_view[
				sge::image2d::l8::view_type::dim(
					x,
					y
				)
			].set(
				mizuiro::color::channel::luminance(),
				static_cast<sge::image::color::channel8>(
					256.0 *
					(0.5 + 0.5 *
					sge::noise::sample(
						noise_generator,
						param_type(
							param_type::position_type(
								noise_type::vector_type(
									static_cast<noise_type::value_type>(
										x),
									static_cast<noise_type::value_type>(
										y))),
							param_type::amplitude_type(
								0.8),
							param_type::frequency_type(
								.005),
							param_type::octaves_type(
								6u))))
				)
			);
		}
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &)
try
{
	typedef
	sge::noise::simplex::object<double,2>
	noise_type;

	noise_type noise_generator(
		sge::noise::simplex::width(
			128u));

	fcppt::io::cout()
		<< FCPPT_TEXT("raw noise generator spit out: ")
		<< noise_generator.sample(
				noise_type::vector_type(
					23.0,
					42.0))
		<< FCPPT_TEXT('\n');

	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::window::dim const window_dim(
		1024,
		1024
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("noisetest")
					),
					window_dim)))
		(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::windowed(
						sge::renderer::bit_depth::depth32),
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::viewport::fill_on_resize()))
	);

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
				sge::sprite::config::texture_coordinates::automatic,
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

	sprite_buffers_type sprite_buffers(
		sys.renderer(),
		sge::sprite::buffers::option::dynamic);

	sge::image2d::l8 store(
		fcppt::math::dim::structure_cast<
			sge::image2d::dim
		>(
			window_dim));

	fill_texture(
		store.view());

	sge::renderer::texture::planar_scoped_ptr const noise_texture(
		sge::renderer::texture::create_planar_from_view(
			sys.renderer(),
			sge::image2d::view::const_object(
				sge::image2d::view::object(
					store.wrapped_view())),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags::none));

	sprite_object const spr(
		sge::sprite::default_parameters<
			sprite_choices
		>()
		.size(
			sprite_object::dim(
				fcppt::math::dim::structure_cast<
					sprite_object::dim
				>(
					window_dim
				)
			)
		)
		.texture(
			fcppt::make_shared_ptr<
				sge::texture::part_raw
			>(
				fcppt::ref(
					*noise_texture
				)
			)
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		sge::sprite::process::one(
			spr,
			sprite_buffers
		);

		sge::renderer::scoped_block const block_(
			sys.renderer());
	}

	return sys.window_system().exit_code();
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr() << e.string() << FCPPT_TEXT("\n");
	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr << _error.what() << '\n';
	return awl::main::exit_failure();
}
