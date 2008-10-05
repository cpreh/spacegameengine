#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/object.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/window.hpp>
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
					640,
					480),
				sge::renderer::bit_depth::depth32),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::image));

	sge::sprite::system ss(sys.renderer());
	sge::image::object_ptr const image = sys.image_loader()->load(SGE_TEXT("tux.png"));
	sge::renderer::texture_ptr const image_texture = 
		sys.renderer()->create_texture(
			image->view(),
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::none);
	sge::sprite::object const my_object(
			sge::sprite::point(0,0),
			sge::make_shared_ptr<
				sge::texture::part_ptr,
				sge::texture::part_raw>(
					image_texture),
			sge::sprite::texture_dim);

	while (true)
	{
			sge::window::dispatch();
			sge::renderer::scoped_block const block_(sys.renderer());
			ss.render(my_object);
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
