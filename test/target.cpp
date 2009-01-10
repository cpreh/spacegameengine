#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/object.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/media.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge targettest")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					1024,
					768),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::image)
		(sge::systems::parameterless::input));

	sge::sprite::system ss(sys.renderer());
	sge::image::object_ptr const image = sys.image_loader()->load(sge::media_path() / SGE_TEXT("tux.png"));
	sge::renderer::texture_ptr const image_texture = 
		sys.renderer()->create_texture(
			image->view(),
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::readable);

	sge::sprite::object my_object(
			sge::sprite::point(100,0),
			sge::texture::const_part_ptr(
				sge::make_shared_ptr<
					sge::texture::part_raw
				>(
					image_texture)),
			sge::sprite::texture_dim);

	sge::sprite::object my_object_2(
			sge::sprite::point(100,20),
			sge::texture::const_part_ptr(
				sge::make_shared_ptr<
					sge::texture::part_raw
				>(image_texture)),
			sge::sprite::texture_dim);
	
	sge::renderer::texture_ptr const target = 
		sys.renderer()->create_texture(
			sge::renderer::texture::dim_type(640,480),
			sge::renderer::color_format::rgba8,
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::none);

	{
		sge::renderer::scoped_block const block_(sys.renderer());
		sys.renderer()->target(target);
		ss.render(my_object);
		ss.render(my_object_2);
	}

	sys.renderer()->target(sge::renderer::device::default_target);

	sge::sprite::object rendered_stuff(
		sge::sprite::point(0,0),
		sge::texture::const_part_ptr(
			sge::make_shared_ptr<
				sge::texture::part_raw
			>(target)),
		sge::sprite::texture_dim);

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color_::clear_color = sge::renderer::colors::red()));

	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	bool running = true;

	sge::signals::scoped_connection const cb(
		sys.input_system()->register_callback(
			if_(
				bind(
					&sge::input::key_type::code,
					bind(
						&sge::input::key_pair::key,
						boost::lambda::_1))
					== sge::input::kc::key_escape)
				[var(running)=false]));

	while (running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(sys.renderer());
		ss.render(rendered_stuff);
	}
} 
catch (sge::exception const &e)
{
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << '\n';
	return EXIT_FAILURE;
}
