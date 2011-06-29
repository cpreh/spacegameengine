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


#include <sge/config/media_path.hpp>
#include <sge/extension_set.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image/capabilities.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/log/global.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/sprite/animation/entity.hpp>
#include <sge/sprite/animation/entity_vector.hpp>
#include <sge/sprite/animation/loop_method.hpp>
#include <sge/sprite/animation/series.hpp>
#include <sge/sprite/animation/texture_impl.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/with_repetition.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/time/default_callback.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/second.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/ref.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <streambuf>
#include <exception>
#include <iostream>
#include <ios>
#include <ostream>
#include <cstdlib>

namespace
{

sge::texture::const_part_ptr const
load_raw(
	fcppt::filesystem::path const &_image_path,
	sge::texture::manager &_tex_man,
	sge::image2d::multi_loader &_image_loader
)
{
	fcppt::io::cifstream raw_stream(
		_image_path,
		std::ios::binary
	);

	typedef
	fcppt::container::raw_vector<char> 
	raw_byte_container;

	raw_byte_container raw_bytes(
		(
			std::istreambuf_iterator<char>(
				raw_stream
			)
		),
		std::istreambuf_iterator<char>()
	);

	return 
		sge::texture::add_image(
			_tex_man,
			*_image_loader.load_raw(
				boost::make_iterator_range(
					reinterpret_cast<
						unsigned char const *
					>(
						&(*raw_bytes.cbegin())
					),
					reinterpret_cast<
						unsigned char const *
					>(
						&(*raw_bytes.cend())
					)
				),
				sge::optional_extension()
			)
		);
}

}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::window::dim const dimensions(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge animtest"),
					dimensions
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
				sge::viewport::center_on_resize(
					dimensions
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<sge::extension_set>(FCPPT_TEXT("png"))
			)
		)
	);

	sge::renderer::device &rend(
		sys.renderer()
	);

	sge::image2d::multi_loader &image_loader(
		sys.image_loader()
	);

	sge::texture::manager tex_man(
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				fcppt::ref(
					rend
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::filter::linear,
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::repeat
				)
			)
		)
	);

	// Just for kicks, try loading an image file from a raw memory buffer
	sge::texture::const_part_ptr const
		tex1(
			load_raw(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("cloudsquare.png"),
				tex_man,
				image_loader
			)
		);

	sge::texture::const_part_ptr const
		tex2(
			sge::texture::add_image(
				tex_man,
				*image_loader.load(
					sge::config::media_path()
					/ FCPPT_TEXT("images")
					/ FCPPT_TEXT("grass.png")
				)
			)
		);

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

	sprite_system ss(
		rend
	);

	sprite_object spr(
		sprite_parameters()
		.pos(
			sprite_object::vector::null()
		)
		.size(
			sprite_object::dim(
				fcppt::math::dim::structure_cast<
					sprite_object::dim
				>(
					dimensions
				)
			)
		)
		.repetition(
			sprite_object::repetition_type(
				2,
				2
			)
		)
		.elements()
	);

	sge::sprite::animation::series const series(
		fcppt::assign::make_container<
			sge::sprite::animation::entity_vector
		>(
			sge::sprite::animation::entity(
				sge::time::millisecond(500),
				tex1
			)
		)
		(
			sge::sprite::animation::entity(
				sge::time::second(
					1
				),
				tex2
			)
		)
	);
	
	typedef sge::sprite::animation::texture<
		sprite_choices
	> texture_animation;

	texture_animation anim(
		series,
		sge::sprite::animation::loop_method::stop_at_end,
		spr,
		sge::time::default_callback()
	);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	rend.state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(
				sge::renderer::state::color::back_buffer_clear_color
					= sge::image::colors::blue()
			)
	);

	while(
		running
	)
	{
		sys.window().dispatch();

		sge::renderer::scoped_block const block_(
			rend
		);

		if(
			anim.process()
		)
			return 0;

		sge::sprite::render_one(
			ss,
			spr
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
