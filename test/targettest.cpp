#include <sge/systems.hpp>
#include <sge/init.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/media.hpp>
#include <exception>
#include <iostream>

int main()
try
{
	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::image_loader>();
	sys.init<sge::init::renderer>(sge::renderer::screen_size_t(640,480));

	sge::sprite::system ss(sys.renderer);
	sge::image::object_ptr image = sys.image_loader->load_image(sge::media_path() / SGE_TEXT("tux.png"));
	sge::renderer::texture_ptr image_texture = 
		sys.renderer->create_texture(
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
	
	sge::renderer::texture_ptr target = 
		sys.renderer->create_texture(
			sge::renderer::texture::dim_type(640,480),
			sge::renderer::color_format::rgba8,
			sge::renderer::linear_filter,
			sge::renderer::resource_flags::dynamic);

	{
		sge::renderer::scoped_block block_(sys.renderer);
		sys.renderer->set_render_target(target);
		ss.render(my_object);
		ss.render(my_object_2);
	}

	sys.renderer->set_render_target(sge::renderer::device::default_render_target);

	sge::sprite::object rendered_stuff(
		sge::sprite::point(0,0),
		sge::texture::part_ptr(new sge::texture::part_raw(target)),
		sge::sprite::texture_dim);

	while (true)
	{
			sge::window::dispatch();
			sge::renderer::scoped_block block_(sys.renderer);
			ss.render(rendered_stuff);
	}
} 
catch (sge::exception const &e)
{
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT("\n");
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << "\n";
}
