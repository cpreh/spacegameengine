#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/object.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/media.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					1024,
					768),
				sge::renderer::bit_depth::depth32),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		//(sge::systems::parameterless::input)
		(sge::systems::parameterless::image));

	sge::sprite::system ss(sys.renderer());
	sge::image::object_ptr const image = sys.image_loader()->load(sge::media_path() / SGE_TEXT("tux.png"));
	sge::renderer::texture_ptr const image_texture = 
		sys.renderer()->create_texture(
			image->view(),
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::readable);

	sge::sprite::object my_object(
			sge::sprite::point(100,0),
			sge::texture::part_ptr(new sge::texture::part_raw(image_texture)),
			sge::sprite::texture_dim);

	sge::sprite::object my_object_2(
			sge::sprite::point(100,20),
			sge::texture::part_ptr(new sge::texture::part_raw(image_texture)),
			sge::sprite::texture_dim);
	
	sge::renderer::texture_ptr const target = 
		sys.renderer()->create_texture(
			sge::renderer::texture::dim_type(640,480),
			sge::renderer::color_format::rgba8,
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::none);

	{
		sge::renderer::scoped_block const block_(sys.renderer());
		sys.renderer()->set_render_target(target);
		ss.render(my_object);
		ss.render(my_object_2);
	}

	sys.renderer()->set_render_target(sge::renderer::device::default_render_target);

	sge::sprite::object rendered_stuff(
		sge::sprite::point(0,0),
		sge::texture::part_ptr(new sge::texture::part_raw(target)),
		sge::sprite::texture_dim);

	while (true)
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
