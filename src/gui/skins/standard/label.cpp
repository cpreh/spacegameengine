#include "../../utility/blit.hpp"
#include "../../utility/max_dim.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/dim/io.hpp>
#include <sge/font/font.hpp>
#include <sge/font/text_size_t.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/media.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <sge/structure_cast.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("skins::standard::label"),
	false);
}

void sge::gui::skins::standard::draw(
	widgets::label const &b,
	events::invalid_area const &e)
{
	// resize internal buffer if neccessary
	if (b.buffer().width() != static_cast<image::coord_t>(b.size().w()) ||
	    b.buffer().height() != static_cast<image::coord_t>(b.size().h()))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1
				<< SGE_TEXT("resizing from ") 
				<< dim(b.buffer().width(),b.buffer().height())
				<< SGE_TEXT(" to ")
				<< b.size());
		b.buffer() = image(
			static_cast<image::coord_t>(b.size().w()),
			static_cast<image::coord_t>(b.size().h()));
	}

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("creating canvas from buffer"));

	canvas::object c(b.buffer());

	// Background
	c.draw_rect(
		rect(c.size()),
		internal_color(0xee,0xee,0xee,0xff),
		canvas::rect_type::solid);

	SGE_ASSERT_MESSAGE(
		b.font(),
		SGE_TEXT("button: font missing while drawing button"));

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("drawing text (label \"")
		        << b.text()
		        << SGE_TEXT("\")"));

	// draw text centered
	c.draw_text(
		b.font(),
		renderer::colors::black(),
		b.text(),
		point::null(),
		c.size(),
		font::align_h::center,
		font::align_v::center);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("blitting (label \"")
		        << b.text()
		        << SGE_TEXT("\")"));

	utility::blit_invalid(
		renderer::make_const_image_view(c.view()),
		rect(b.pos(),c.size()),
		e.texture(),
		e.area());
}

sge::gui::dim const sge::gui::skins::standard::size_hint(
	widgets::label const &b) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("calling size hint for label"));

	font::font fn(b.font());	

	// NOTE: we have to give text_size a huge rectangle because it won't
	// return a valid rectangle otherwise
	dim const font_dim = structure_cast<dim>(
		fn.text_size(
			b.text(),
			utility::max_dim<font::unit>()).size());

	return dim(static_cast<unit>(font_dim.w()),static_cast<unit>(font_dim.h()));
}
