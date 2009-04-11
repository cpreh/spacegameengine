#include "../../utility/max_dim.hpp"
#include "../../utility/string_square.hpp"
#include "../../utility/blit.hpp"
#include <sge/gui/internal_color.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/skins/standard.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/structure_cast.hpp>
#include <boost/gil/image.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),SGE_TEXT("skins: standard: edit"),
	false);
}

sge::gui::dim const sge::gui::skins::standard::size_hint(
	widgets::edit const &w) const
{
	dim const d = structure_cast<dim>(
		font::object(w.font()).text_size(
			utility::string_square(w.desired_size()),
			utility::max_dim<font::unit>())
		.size());
	
	return dim(
		d.w() + 2,
		d.h() + 2);
}

void sge::gui::skins::standard::draw(
	widgets::edit const &w,
	events::invalid_area const &e)
{
	if (w.size() == dim::null())
		return;

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("refreshing edit buffer"));
	// re-render text buffer
	w.refresh();
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("refreshed edit buffer"));
	
	resize_buffer(w);

	canvas::object c(w.buffer());

	// fill completely with background color
	c.draw_rect(
		c.area(),
	//	internal_color(0x55,0x55,0x55,0xff),
		internal_color(0xff,0xff,0xff,0xff),
		canvas::rect_type::solid);
	
	dim const buffer_size = dim(
		static_cast<unit>(w.text_buffer().width()),
		static_cast<unit>(w.text_buffer().height()));

	point const scroll_origin = w.scroll_pos();

	dim const scroll_size = buffer_size - dim(scroll_origin.x(),scroll_origin.y());
	
	utility::blit(
		renderer::const_image_view(
			boost::gil::const_view(
				w.text_buffer())),
		rect(
			scroll_origin,
			scroll_size),
		c.view(),
		rect(
			point(1,1),
			scroll_size),
		rect(
			point(1,1),
			dim(w.size().w()-2,w.size().h()-2)
			)
		);

	blit_invalid(w,c,e);
}
