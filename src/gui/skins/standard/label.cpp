#include "../../utility/max_dim.hpp"
#include "../../utility/string_square.hpp"
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/internal_color.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/unit.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <sge/renderer/colors.hpp>
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
	resize_buffer(b);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("creating canvas from buffer"));

	canvas::object c(b.buffer());

	// Background
	/*
	c.draw_rect(
		rect(c.size()),
		internal_color(0xee,0xee,0xee,0xff),
		canvas::rect_type::solid);
		*/
	c.draw_rect(
		rect(c.size()),
		internal_color(0x0,0x0,0x0,0x0),
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
		b.color(),
		b.text(),
		point::null(),
		c.size(),
		b.align_h(),
		b.align_v());

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("blitting (label \"")
		        << b.text()
		        << SGE_TEXT("\")"));

	blit_invalid(
		b,
		c,
		e,
		true);
}

sge::gui::dim const sge::gui::skins::standard::size_hint(
	widgets::label const &b) const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("calling size hint for label"));

	font::object fn(b.font());	

	// NOTE: we have to give text_size a huge rectangle because it won't
	// return a valid rectangle otherwise
	dim const font_dim = structure_cast<dim>(
		fn.text_size(
			b.static_size() 
				? utility::string_square(*b.static_size()) 
				: b.text(),
			utility::max_dim<font::unit>()).size());

	return dim(
		static_cast<unit>(font_dim.w()),
		static_cast<unit>(font_dim.h()));
}
