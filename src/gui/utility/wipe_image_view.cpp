#include "wipe_image_view.hpp"
#include <sge/renderer/colors.hpp>
#include <sge/renderer/fill_pixels.hpp>

void sge::gui::utility::wipe_image_view(
	renderer::image_view const &v)
{
	renderer::fill_pixels(
		v,
		renderer::colors::transparent());
}
