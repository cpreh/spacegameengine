#include "../extensions.hpp"
#include "../renderer_system.hpp"
#include "../renderer.hpp"

sge::renderer_ptr sge::ogl::renderer_system::create_renderer(
	const renderer_parameters& param, const int adapter)
{
	return renderer_ptr(new renderer(param,adapter));
}

void sge::ogl::renderer_system::get_renderer_caps(renderer_caps_array& v) const
{
}
