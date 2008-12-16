#include <sge/gui/canvas/font_drawer.hpp>
#include <sge/math/rect.hpp>
#include <sge/renderer/transform_pixels.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/subimage_view.hpp>
#include "utility/font_blitter.hpp"

sge::gui::canvas::font_drawer::font_drawer(
	image_view &texture_,
	color c)
	: texture_(texture_),
	  c(c)
{
}

void sge::gui::canvas::font_drawer::begin_rendering(
	size_type const /*buffer_chars*/,
	font::pos const &/*pos*/,
	font::dim const /*size*/)
{
}

void sge::gui::canvas::font_drawer::draw_char(
	char_type const, 
	font::pos const &p, 
	font::const_image_view const &data)
{
	image_view const sub_view = renderer::subimage_view(
			texture_,
			renderer::lock_rect(
				static_cast<renderer::size_type>(p.x()),
				static_cast<renderer::size_type>(p.y()),
				static_cast<renderer::size_type>(p.x()+data.width()),
				static_cast<renderer::size_type>(p.y()+data.height())));
	
	renderer::transform_pixels(
		data,
		renderer::make_const_image_view(sub_view),
		sub_view,
		utility::font_blitter(c));
}

void sge::gui::canvas::font_drawer::end_rendering()
{
}
