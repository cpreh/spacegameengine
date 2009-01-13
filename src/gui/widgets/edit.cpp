#include "../utility/max_dim.hpp"
#include <sge/gui/events/key.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/log.hpp>
#include <sge/gui/timer/object.hpp>
#include <sge/gui/canvas.hpp>
#include <sge/gui/manager.hpp>
#include <sge/time/second_f.hpp>
#include <sge/math/compare.hpp>
#include <boost/bind.hpp>
#include <locale>

namespace
{
sge::gui::logger mylogger(sge::gui::widgets::global_log(),SGE_TEXT("edit"),true);
}

sge::gui::widgets::edit::edit(
	parent_data parent,
	dim const &desired_size_,
	font::metrics_ptr const _font)
	: widget(
			parent,
			size_policy::default_policy,
			keyboard_focus::receive),
	  font_(_font),
		desired_size_(desired_size_),
		cursor_visible_(true),
		text_buffer_(),
		scroll_pos_(point::null()),
		cursor_pos(static_cast<string::size_type>(0))
{
	if (!font_)
		font_ = parent_manager().standard_font();

	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("edit: no standard font could be set by manager"));
}

sge::string const sge::gui::widgets::edit::text() const
{
	return text_;
}

void sge::gui::widgets::edit::text(string const &n)
{
	text_ = n;
	parent_manager().invalidate(absolute_area());
}

sge::font::metrics_ptr const sge::gui::widgets::edit::font() const
{
	return font_;
}

sge::gui::point const &sge::gui::widgets::edit::scroll_pos() const
{
	return scroll_pos_;
}

sge::gui::dim const sge::gui::widgets::edit::desired_size() const
{
	return desired_size_;
}

sge::gui::image &sge::gui::widgets::edit::text_buffer()
{
	return text_buffer_;
}

sge::gui::image const &sge::gui::widgets::edit::text_buffer() const
{
	return text_buffer_;
}

void sge::gui::widgets::edit::process(events::keyboard_enter const &)
{
	timer_ = 
		parent_manager().register_timer(
			sge::time::second_f(static_cast<time::funit>(0.5)),
			boost::bind(&edit::blink_callback,this));
}

sge::gui::key_handling::type sge::gui::widgets::edit::process(events::key const &k)
{
	if (math::almost_zero(k.value().value()))
		return key_handling::process;
	
	if (k.value().key().char_code() != 0)
		text_ += k.value().key().char_code();

	parent_manager().invalidate(absolute_area());

	return key_handling::process;
}

void sge::gui::widgets::edit::process(events::keyboard_leave const &)
{
	timer_.reset();
}

void sge::gui::widgets::edit::blink_callback()
{
	cursor_visible_ = !cursor_visible_;
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("blinking cursor, visibility: ") << cursor_visible_);
	parent_manager().invalidate(absolute_area());
}

void sge::gui::widgets::edit::resize(dim const &d) const
{
	dim const text_size(
		static_cast<unit>(text_buffer_.width()),
		static_cast<unit>(text_buffer_.height()));

	if (text_size.w() > d.w() && text_size.h() > d.h())
	{
		SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("no resize needed"));
		return;
	}
	
	image nb(
		static_cast<image::coord_t>(text_size.w() >= d.w() ? text_size.w() : d.w()),
		static_cast<image::coord_t>(text_size.h() >= d.h() ? text_size.h() : d.h()));
	
	text_buffer_ = nb;
}

void sge::gui::widgets::edit::refresh() const
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("redrawing text buffer"));

	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("getting font size"));
	dim const d = math::structure_cast<unit>(
		font::font(font()).text_size(
			text(),
			utility::max_dim<font::unit>())
		.size());

	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("resizing buffer"));
	
	// text larger than buffer? resize!
	resize(d);

	canvas::object c(text_buffer_);

	// TODO: use a transparent background here and blit it with alpha blending
	// enabled OR introduce widgets::edit::background_color
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("filling background"));

	c.draw_rect(
		c.area(),
		internal_color(0xff,0xff,0xff,0xff),
		canvas::rect_type::solid);
	
	if (!text().empty())
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("drawing text: ") << text());

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("cursor position is: ") << cursor_pos);

		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << SGE_TEXT("text buffer size is: ")
							<< dim(text_buffer_.width(),text_buffer_.height()));

		point p;
		c.draw_text(
			font(),
			internal_color(0x00,0x00,0x00,0xff),
			text(),
			point::null(),
			dim(
				static_cast<unit>(text_buffer_.width()),
				static_cast<unit>(text_buffer_.height())),
			font::align_h::left,
			font::align_v::top,
			font::flags::default_,
			cursor_pos,
			&p);
	
		if (cursor_visible_)
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("drawing cursor at ") << p);

			unit const cursor_height = 
				std::min(
					static_cast<unit>(font()->line_height()/2),
					c.area().h());

			// draw cursor
			c.draw_line(
				p,
				point(p.x(),p.y()+cursor_height),
				internal_color(0x00,0x00,0x00,0xff));
		}
	}
}
