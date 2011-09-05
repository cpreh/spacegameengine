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


#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/window/instance.hpp>
#include <sge/config/media_path.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/audio/player.hpp>
#include <sge/log/global.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_ptr.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/relative_movement.hpp>
#include <sge/input/cursor/relative_move_event.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/object_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_depth.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/default_sort.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <streambuf>
#include <ostream>
#include <vector>
#include <ios>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>

namespace
{
sge::audio::file_ptr const
load_raw(
	fcppt::filesystem::path const &path,
	sge::audio::multi_loader &audio_loader)
{
	fcppt::io::cifstream raw_stream(
		path,
		std::ios::binary);

	typedef
	fcppt::container::raw_vector<char>
	raw_byte_container;

	raw_byte_container raw_bytes(
		(std::istreambuf_iterator<char>(
			raw_stream)),
		std::istreambuf_iterator<char>());

	return
		audio_loader.load_raw(
			boost::make_iterator_range(
				reinterpret_cast<unsigned char const *>(
					&(*raw_bytes.cbegin())),
				reinterpret_cast<unsigned char const *>(
					&(*raw_bytes.cend()))),
			sge::optional_extension());
}
}

namespace
{

typedef sge::image::color::rgba8_format sprite_color;

typedef sge::sprite::choices<
	sge::sprite::type_choices<
		int,
		float,
		sprite_color
	>,
	boost::mpl::vector4<
		sge::sprite::with_color,
		sge::sprite::with_texture,
		sge::sprite::with_depth,
		sge::sprite::with_dim
	>
> sprite_choices;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

class sprite_functor
{
	FCPPT_NONASSIGNABLE(
		sprite_functor
	);
public:
	explicit sprite_functor(
		sge::audio::sound::positional_ptr const _sound
	)
	:
		sound_(_sound)
	{}

	void
	normal_movement(
		sge::input::cursor::move_event const &_event
	) const
	{
		sound_->position(
			sge::audio::vector(
				static_cast<
					sge::audio::scalar
				>(
					_event.position().x()
				),
				static_cast<sge::audio::scalar>(0),
				static_cast<
					sge::audio::scalar
				>(
					_event.position().y()
				)
			)
		);
	}

	void
	relative_movement(
		sge::input::cursor::relative_move_event const &_event
	)
	{
		sound_->linear_velocity(
			sge::audio::vector(
				static_cast<
					sge::audio::scalar
				>(
					_event.position().x()
				),
				sound_->linear_velocity().y(),
				static_cast<
					sge::audio::scalar
				>(
					_event.position().y()
				)
			)
		);
	}
private:
	sge::audio::sound::positional_ptr const sound_;
};
}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge dopplertest"),
					window_dim
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
					window_dim
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::cursor_demuxer,
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::audio_player_default()
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("png")
				)
			)
		)
		(
			sge::systems::audio_loader(
				sge::audio::loader_capabilities_field::null(),
				fcppt::assign::make_container<
					sge::extension_set
				>(
					FCPPT_TEXT("ogg")
				)
			)
		)
	);

	sge::input::cursor::object &cursor(
		sys.cursor_demuxer()
	);

	sge::image2d::file_ptr const
		image_bg(
			sys.image_loader().load(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("grass.png")
			)
		),
		image_tux(
			sys.image_loader().load(
				sge::config::media_path()
				/ FCPPT_TEXT("images")
				/ FCPPT_TEXT("tux.png")
			)
		);

	sge::texture::manager tex_man(
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				fcppt::ref(
					sys.renderer()
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::repeat
				)
			)
		)
	);

	sge::texture::const_part_ptr const
		tex_bg(
			sge::texture::add_image(
				tex_man,
				*image_bg
			)
		),
		tex_tux(
			sge::texture::add_image(
				tex_man,
				*image_tux
			)
		);

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_system ss(
		sys.renderer()
	);

	sprite_object bg(
		sprite_parameters()
		.texture(
			tex_bg
		)
		.pos(
			sprite_object::vector::null()
		)
		.size(
			fcppt::math::dim::structure_cast<
				sprite_object::dim
			>(
				window_dim
			)
		)
		.depth(
			static_cast<
				sprite_object::depth_type
			>(0)
		)
		.default_color()
		.elements()
	);

	sprite_object tux(
		sprite_parameters()
		.pos(
			sprite_object::vector(
				static_cast<
					sprite_object::unit
				>(
					window_dim.w()
					/
					2
					-16u
				),
				static_cast<
					sprite_object::unit
				>(
					window_dim.h()
					/
					2
					-16u
				)
			)
		)
		.texture(
			tex_tux
		)
		.size(
			sprite_object::dim(32,32)
		)
		.default_color()
		.depth(
			static_cast<
				sprite_object::depth_type
			>(1)
		)
		.elements()
	);

	sge::audio::file_ptr const af_siren(
		load_raw(
			sge::config::media_path()
			/ FCPPT_TEXT("sounds")
			/ FCPPT_TEXT("siren.ogg"),
			sys.audio_loader()
		)
	);

	sge::audio::sound::positional_ptr const sound_siren(
		sys.audio_player().create_positional_stream(
			af_siren,
			sge::audio::sound::positional_parameters()
			.rolloff(
				static_cast<sge::audio::scalar>(1)
				/ static_cast<sge::audio::scalar>(window_dim.h())
			)
		)
	);

	sys.audio_player().listener().position(
		sge::audio::vector(
			static_cast<sge::audio::scalar>(window_dim.w()/2),
			static_cast<sge::audio::scalar>(0),
			static_cast<sge::audio::scalar>(window_dim.h()/2)
		)
	);

	sys.audio_player().speed_of_sound(
		static_cast<sge::audio::scalar>(500)
	);

	sound_siren->play(
		sge::audio::sound::repeat::loop
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

	::sprite_functor functor(
		sound_siren
	);

	fcppt::signal::scoped_connection const normal_connection(
		cursor.move_callback(
			std::tr1::bind(
				&::sprite_functor::normal_movement,
				&functor,
				std::tr1::placeholders::_1
			)
		)
	);

	sge::input::cursor::relative_movement rel_movement(
		cursor
	);

	fcppt::signal::scoped_connection const relative_connection(
		rel_movement.relative_move_callback(
			std::tr1::bind(
				&::sprite_functor::relative_movement,
				&functor,
				std::tr1::placeholders::_1
			)
		)
	);


	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::color::back_buffer_clear_color = sge::image::colors::black())
	);

	while(running)
	{
		sys.window().dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		std::vector<
			sprite_object
		> sprites;

		sprites.push_back(bg);
		sprites.push_back(tux);

		ss.render(
			sprites.begin(),
			sprites.end(),
			sge::sprite::default_sort(),
			sge::sprite::default_equal()
		);

		sound_siren->update();
	}
}
catch(sge::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	fcppt::io::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
