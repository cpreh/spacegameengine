#include <sge/gui/create_texture.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>


sge::renderer::texture::planar_unique_ptr
sge::gui::create_texture(
	sge::renderer::device::core &_renderer,
	sge::image2d::view::const_object const &_view
)
{
	return
		sge::renderer::texture::create_planar_from_view(
			_renderer,
			_view,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::no
		);
}
