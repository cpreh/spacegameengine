#include "../../utility/max_dim.hpp"
#include "../../utility/blit.hpp"
#include <sge/font/font.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/iostream.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/skins/standard.hpp>
#include <boost/gil/image.hpp>

namespace
{
sge::string const string_square(sge::gui::dim const &s)
{
	sge::string const line(
		static_cast<sge::string::size_type>(s.w()),
		SGE_TEXT('W'));
	sge::string result;
	for (sge::gui::unit i = 0; i < s.h(); ++i)
		result += line;
	return result;
}
}

sge::gui::dim const sge::gui::skins::standard::size_hint(
	widgets::edit const &w) const
{
	dim d = math::structure_cast<unit>(
		font::font(w.font()).text_size(
			string_square(w.desired_size()),
			utility::max_dim<font::unit>())
		.size());
	
	return dim(
		d.w()+2,
		d.h()+2);
}

void sge::gui::skins::standard::draw(
	widgets::edit const &w,
	events::invalid_area const &e)
{
	// re-render text buffer
	w.refresh();
	
	// resize internal buffer
	if (w.buffer().width() != w.size().w() || w.buffer().height() != w.size().h())
	{
		w.buffer() = image(
			static_cast<image::coord_t>(w.size().w()),
			static_cast<image::coord_t>(w.size().h()));
	}

	canvas::object c(w.buffer());

	// fill completely with background color
	c.draw_rect(
		c.area(),
		internal_color(0x55,0x55,0x55,0xff),
		canvas::rect_type::solid);
	
	dim const buffer_size = dim(
		static_cast<unit>(w.text_buffer().width()),
		static_cast<unit>(w.text_buffer().height()));

	// blit the image at position 1,1
	utility::blit(
		renderer::const_image_view(
			boost::gil::const_view(
				w.text_buffer())),
		rect(
			point::null(),
			buffer_size),
		c.view(),
		rect(
			point(1,1),
			buffer_size),
		rect(
			point(1,1),
			dim(w.size().w()-2,w.size().h()-2)
			)
		);

	utility::blit_invalid(
		renderer::make_const_image_view(c.view()),
		rect(w.pos(),c.size()),
		e.texture(),
		e.area());
}
