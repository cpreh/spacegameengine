/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/config/media_path.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/audio/player.hpp>
#include <sge/log/global.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sound.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/input/system.hpp>
#include <sge/input/action.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/key_code.hpp>
#include <sge/image/multi_loader.hpp>
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
#include <sge/sprite/default_sort.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/io/cerr.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <ostream>
#include <vector>
#include <cstdlib>

namespace
{

typedef sge::image::color::rgba8_format sprite_color;

typedef sge::sprite::choices<
	sge::sprite::type_choices<
		int,
		float,
		sprite_color
	>,
	boost::mpl::vector3<
		sge::sprite::with_color,
		sge::sprite::with_texture,
		sge::sprite::with_depth
	> 
> sprite_choices;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

class sprite_functor
{
public:
	explicit sprite_functor(
		sprite_object &s,
		sge::audio::sound_ptr const sound
	)
	:
		s(s),
		sound(sound)
	{}

	void
	operator()(
		sge::input::key_pair const &k
	) const
	{
		switch (k.key().code())
		{
		case sge::input::kc::mouse_x_axis:
			s.x(
				s.x() + k.value()
			);

			sound->vel(
				sge::audio::vector(
					static_cast<sge::audio::scalar>(k.value()),
					sound->vel().y(),
					sound->vel().z()
				)
			);

			break;
		case sge::input::kc::mouse_y_axis:
			s.y(
				s.y() + k.value()
			);

			sound->vel(
				sge::audio::vector(
					sound->vel().x(),
					sound->vel().y(),
					static_cast<sge::audio::scalar>(k.value())
				)
			);

			break;

		default:
			break;
		}

		sound->pos(
			sge::audio::vector(
				static_cast<sge::audio::scalar>(s.pos().x()),
				static_cast<sge::audio::scalar>(0),
				static_cast<sge::audio::scalar>(s.pos().y())
			)
		);
	}
private:
	sprite_object &s;
	sge::audio::sound_ptr const sound;
};
}

int main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::renderer::screen_size const screen_size(
		1024,
		768
	);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("sge dopplertest")
			)
		)
		(
			sge::renderer::parameters(
				sge::renderer::display_mode(
					screen_size,
					sge::renderer::bit_depth::depth32,
					sge::renderer::refresh_rate_dont_care
				),
				sge::renderer::depth_buffer::off,
				sge::renderer::stencil_buffer::off,
				sge::renderer::window_mode::windowed,
				sge::renderer::vsync::on,
				sge::renderer::no_multi_sampling
			)
		)
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::audio_player)
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

	sge::image::file_ptr const
		image_bg(
			sys.image_loader().load(
				sge::config::media_path()
				/ FCPPT_TEXT("grass.png")
			)
		),
		image_vectorer(
			sys.image_loader().load(
				sge::config::media_path()
				/ FCPPT_TEXT("gui")
				/ FCPPT_TEXT("cursor.png")
			)
		),
		image_tux(
			sys.image_loader().load(
				sge::config::media_path()
				/ FCPPT_TEXT("tux.png")
			)
		);

	typedef sge::texture::default_creator<
		sge::texture::no_fragmented
	> texture_creator;
	
	texture_creator const
		creator(
			sys.renderer(),
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear
		);

	sge::texture::manager tex_man(
		sys.renderer(),
		creator
	);

	sge::texture::const_part_ptr const
		tex_bg(
			sge::texture::add_image(
				tex_man,
				image_bg
			)
		),
		tex_vectorer(
			sge::texture::add_image(
				tex_man,
				image_vectorer
			)
		),
		tex_tux(
			sge::texture::add_image(
				tex_man,
				image_tux
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
			sprite_object::point::null()
		)
		.size(
			fcppt::math::dim::structure_cast<
				sprite_object::dim
			>(
				screen_size
			)
		)
		.depth(
			static_cast<
				sprite_object::depth_type
			>(2)
		)
		.default_color()
		.elements()
	);

	sprite_object vectorer(
		sprite_parameters()
		.texture(
			tex_vectorer
		)
		.depth(
			static_cast<
				sprite_object::depth_type
			>(0)
		)
		.pos(
			sprite_object::point::null()
		)
		.default_color()
		.texture_size()
		.elements()
	);

	sprite_object tux(
		sprite_parameters()
		.pos(
			sprite_object::point(
				screen_size.w()/2-16,
				screen_size.h()/2-16
			)
		)
		.texture(
			tex_tux
		)
		.size(
			sprite_object::dim(32,32)
		)
		.color(
			sge::image::color::rgba8(
				(sge::image::color::init::red %= 1.0)
				(sge::image::color::init::green %= 1.0)
				(sge::image::color::init::blue %= 1.0)
				(sge::image::color::init::alpha %= 0.25)
			)
		)
		.depth(
			static_cast<
				sprite_object::depth_type
			>(1)
		)
		.elements()
	);

	sge::audio::file_ptr const af_siren(
		sys.audio_loader().load(
			sge::config::media_path()
			/ FCPPT_TEXT("siren.ogg")
		)
	);

	sge::audio::sound_ptr const sound_siren(
		sys.audio_player()->create_nonstream_sound(
			af_siren
		)
	);

	sys.audio_player()->listener().pos(
		sge::audio::vector(
			static_cast<sge::audio::scalar>(screen_size.w()/2),
			static_cast<sge::audio::scalar>(0),
			static_cast<sge::audio::scalar>(screen_size.h()/2)
		)
	);

	sys.audio_player()->speed_of_sound(
		static_cast<sge::audio::scalar>(500)
	);

	sound_siren->positional(
		true
	);

	sound_siren->rolloff(
		static_cast<sge::audio::scalar>(1)
		/ static_cast<sge::audio::scalar>(screen_size.h())
	);

	sound_siren->play(
		sge::audio::play_mode::loop
	);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	fcppt::signal::scoped_connection const pc(
		sys.input_system()->register_callback(
			sprite_functor(
				vectorer,
				sound_siren
			)
		)
	);

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black())
	);

	while(running)
	{
		sge::mainloop::dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		std::vector<
			sprite_object
		> sprites;

		sprites.push_back(bg);
		sprites.push_back(vectorer);
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
