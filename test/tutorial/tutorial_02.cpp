#include <sge/systems.hpp>
#include <sge/init.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/input/key_type.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/scoped_connection.hpp>
#include <exception>
#include <iostream>

namespace
{
class input_functor
{
    public:
    input_functor(bool &running) 
        : running(running) 
    {
    }

    void operator()(sge::input::key_pair const &k) const
    {
        if (k.key().code() == sge::input::kc::key_escape)
            running = false;
    }
    private:
    bool &running;
};

class sprite_functor
{
    public:
    sprite_functor(sge::sprite::object &s) 
			: s(s) 
		{}

    void operator()(sge::input::key_pair const &k) const
    {
        switch (k.key().code())
        {
            case sge::input::kc::mouse_x_axis:
            s.pos().x() += k.value();
            break;
            case sge::input::kc::mouse_y_axis:
            s.pos().y() += k.value();
            break;
            default: break;
        }
    }
    private:
    sge::sprite::object &s;
};
}

int main()
try
{
    sge::systems sys;
    sys.init<sge::init::core>();
    sys.init<sge::init::image_loader>();
    sys.init<sge::init::renderer>(sge::renderer::screen_size_t(640,480));
		sys.init<sge::init::input>();

    sge::sprite::system ss(sys.renderer);
    sge::image::object_ptr image = 
        sys.image_loader->load_image(SGE_TEXT("tux.png"));
		sge::renderer::texture_ptr image_texture = 
			sys.renderer->create_texture(
				image->view(),
				sge::renderer::linear_filter,
				sge::renderer::resource_flags::readable);
    sge::sprite::object my_object(
            sge::sprite::point(0,0),
            sge::texture::part_ptr(new sge::texture::part_raw(image_texture)),
            sge::sprite::texture_dim);

    bool running = true;

    sge::scoped_connection conn = 
        sys.input_system->register_callback(input_functor(running));

    sge::scoped_connection conn_other =
        sys.input_system->register_callback(sprite_functor(my_object));

    while (running)
    {
            sge::window::dispatch();
            sge::renderer::scoped_block block_(sys.renderer);
            ss.render(my_object);
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
