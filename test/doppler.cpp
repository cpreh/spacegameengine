/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/cerr.hpp>
#include <sge/media.hpp>
#include <sge/exception.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/audio/player.hpp>
#include <sge/log/headers.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sound.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/input/system.hpp>
#include <sge/input/action.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/key_code.hpp>
#include <sge/image/loader.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/texture_animation.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/structure_cast.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/assign/list_of.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

namespace
{
class sprite_functor
{
	public:
	explicit sprite_functor(sge::sprite::object &s,sge::audio::sound_ptr const sound)
			: s(s),sound(sound)
		{}

	void operator()(sge::input::key_pair const &k) const
	{
		switch (k.key().code())
		{
			case sge::input::kc::mouse_x_axis:
			s.pos().x() += k.value();
			sound->vel(
				sge::audio::point(
					static_cast<sge::audio::unit>(k.value()),
					sound->vel().y(),
					sound->vel().z()));
			break;
			case sge::input::kc::mouse_y_axis:
			s.pos().y() += k.value();
			sound->vel(
				sge::audio::point(
					sound->vel().x(),
					sound->vel().y(),
					static_cast<sge::audio::unit>(k.value())));
			break;
			default: break;
		}

		sound->pos(
			sge::audio::point(
				static_cast<sge::audio::unit>(s.pos().x()),
				static_cast<sge::audio::unit>(0),
				static_cast<sge::audio::unit>(s.pos().y())));
	}
	private:
	sge::sprite::object &s;
	sge::audio::sound_ptr const sound;
};
}

int main()
try
{
	sge::log::global().activate_hierarchy(
		sge::log::level::debug);
	sge::renderer::screen_size const screen_size(1024,768);
	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge dopplertest")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				screen_size,
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::audio_player)
		(sge::systems::parameterless::image));
	
	sge::image::object_ptr const 
		image_bg(
			sys.image_loader()->load(
				sge::media_path()/SGE_TEXT("grass.png"))),
		image_pointer(
			sys.image_loader()->load(
				sge::media_path()/SGE_TEXT("mainskin")/SGE_TEXT("cursor.png"))),
		image_tux(
			sys.image_loader()->load(
				sge::media_path()/SGE_TEXT("tux.png")));

	sge::texture::default_creator<sge::texture::no_fragmented> const 
		creator(
			sys.renderer(),
			sge::renderer::color_format::rgba8,
			sge::renderer::filter::linear);

	sge::texture::manager tex_man(sys.renderer(),creator);

	sge::texture::const_part_ptr const 
		tex_bg(
			sge::texture::add_image(
				tex_man, 
				image_bg)),
		tex_pointer(
			sge::texture::add_image(
				tex_man, 
				image_pointer)),
		tex_tux(
			sge::texture::add_image(
				tex_man, 
				image_tux));
	
	sge::sprite::system ss(sys.renderer());

	sge::sprite::object bg(
		sge::sprite::parameters()
			.texture(tex_bg)
			.size(
				sge::structure_cast<sge::sprite::dim>(
					screen_size)));

	sge::sprite::object pointer(
		sge::sprite::point(0,0),
		tex_pointer,
		sge::sprite::texture_dim);

	sge::sprite::object tux(
		sge::sprite::point(screen_size.w()/2-16,screen_size.h()/2-16),
		tex_tux,
		sge::sprite::dim(32,32));

	sge::audio::multi_loader ml(sys.plugin_manager());
	sge::audio::file_ptr const af_siren = ml.load(sge::media_path()/SGE_TEXT("siren.ogg"));
	sge::audio::sound_ptr const sound_siren = sys.audio_player()->create_nonstream_sound(af_siren);
	sys.audio_player()->listener().pos(
		sge::audio::point(
			static_cast<sge::audio::unit>(screen_size.w()/2),
			static_cast<sge::audio::unit>(0),
			static_cast<sge::audio::unit>(screen_size.h()/2)));
	sys.audio_player()->speed_of_sound(static_cast<sge::audio::unit>(500));
	sound_siren->positional(true);
	sound_siren->rolloff(static_cast<sge::audio::unit>(1)/static_cast<sge::audio::unit>(screen_size.h()));
	sound_siren->play(sge::audio::play_mode::loop);

	bool running = true;

	sge::signals::scoped_connection const cb(
		sys.input_system()->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	sge::signals::scoped_connection const pc(
		sys.input_system()->register_callback(sprite_functor(pointer,sound_siren)));

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = sge::renderer::rgba8_color(0, 0, 0, 0))
	);

	while(running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(sys.renderer());
		sge::sprite::container sprites;
		sprites.push_back(bg);
		sprites.push_back(pointer);
		sprites.push_back(tux);
		ss.render(sprites.begin(),sprites.end());
		sound_siren->update();
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
