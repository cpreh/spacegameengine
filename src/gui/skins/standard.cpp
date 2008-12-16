#include <sge/gui/skins/standard.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/media.hpp>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("skin"),true);
}

namespace
{
void blit(
	sge::gui::const_image_view const &src,
	sge::gui::rect const &src_rect,
	sge::gui::image_view const dst,
	sge::gui::rect const &dst_rect)
{
	// Calculate intersection of source and destination
	sge::gui::rect const is = sge::math::intersection(
		src_rect,
		dst_rect);
	
	// No intersection? then leave now.
	if (is == sge::gui::rect::null())
	{
		SGE_LOG_DEBUG(
			mylogger,
			sge::log::_1 << SGE_TEXT("no intersection, not blitting"));
		return;
	}

	SGE_LOG_DEBUG(
		mylogger,
		sge::log::_1 << SGE_TEXT("intersection from ")
		             << src_rect
								 << SGE_TEXT(" with ")
								 << dst_rect
								 << SGE_TEXT(" is ")
								 << is);
	
	// Move intersection rect to origin of invalid rect
	sge::gui::rect const is_translated(
		is.pos()-dst_rect.pos(),
		is.dim());
	
	// Get sub view(s) and blit
	sge::renderer::copy_and_convert_pixels(
		src,
		sge::renderer::subimage_view(
			dst,
			sge::math::structure_cast<sge::renderer::size_type>(
				is_translated)));
}
}

sge::gui::skins::standard::standard()
	: bgcolor(renderer::colors::grey()),
		bgcolor_focused(renderer::colors::lightgrey())
{
}

void sge::gui::skins::standard::operator()(
	widgets::button &b,
	events::invalid_area const &e)
{
	// resize internal buffer if neccessary
	if (b.buffer().width() != static_cast<image::coord_t>(b.size().w()) ||
	    b.buffer().height() != static_cast<image::coord_t>(b.size().h()))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("resizing from ") 
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
		b.mouse_over() 
			? internal_color(0xee,0xeb,0xe7,0xff)
			: internal_color(0xdc,0xda,0xd5,0xff),
		canvas::rect_type::solid);
	
	c.draw_line(
		point(0,0),
		point(c.size().w()-1,0),
		internal_color(0xff,0xff,0xff,0xff));

	c.draw_line(
		point(0,0),
		point(0,c.size().h()-1),
		internal_color(0xff,0xff,0xff,0xff));

	c.draw_line(
		point(c.size().w()-2,1),
		point(c.size().w()-2,c.size().h()-2),
		internal_color(0x9e,0x9a,0x91,0xff));

	c.draw_line(
		point(1,c.size().h()-2),
		point(c.size().w()-2,c.size().h()-2),
		internal_color(0x9e,0x9a,0x91,0xff));

	c.draw_line(
		point(c.size().w()-1,0),
		point(c.size().w()-1,c.size().h()-1),
		internal_color(0x00,0x00,0x00,0x00));

	c.draw_line(
		point(0,c.size().h()-1),
		point(c.size().w()-1,c.size().h()-1),
		internal_color(0x00,0x00,0x00,0x00));
	
	if (b.key_over())
	{
		c.draw_line(
			point(2,2),
			point(c.size().w()-3,2),
			internal_color(0x00,0x00,0x00,0x00),
			canvas::line_type::dashed);

		c.draw_line(
			point(c.size().w()-3,2),
			point(c.size().w()-3,c.size().h()-3),
			internal_color(0x00,0x00,0x00,0x00),
			canvas::line_type::dashed);

		c.draw_line(
			point(c.size().w()-3,c.size().h()-3),
			point(2,c.size().h()-3),
			internal_color(0x00,0x00,0x00,0x00),
			canvas::line_type::dashed);

		c.draw_line(
			point(2,c.size().h()-3),
			point(2,2),
			internal_color(0x00,0x00,0x00,0x00),
			canvas::line_type::dashed);
	}

	SGE_ASSERT_MESSAGE(
		b.font(),
		SGE_TEXT("button: font missing while drawing button"));

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("drawing text (button \"")
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
		log::_1 << SGE_TEXT("blitting (button \"")
		        << b.text()
		        << SGE_TEXT("\")"));

	blit(
		renderer::make_const_image_view(c.view()),
		rect(b.pos(),c.size()),
		e.texture(),
		e.area());
}


sge::path const sge::gui::skins::standard::cursor_path() const
{
	return media_path()/SGE_TEXT("mainskin")/SGE_TEXT("cursor_pressed.png");
}
