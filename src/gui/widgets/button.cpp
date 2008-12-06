#include <sge/gui/widgets/button.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/max_dim.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/font_drawer_canvas.hpp>
#include <sge/input/key_type.hpp>
#include <sge/renderer/scoped_lock.hpp>
#include <sge/iostream.hpp>
#include <sge/assert.hpp>
#include <sge/font/font.hpp>
#include <sge/math/rect_impl.hpp>
#include <iostream>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("button"),true);
}

sge::gui::widgets::button::button(
	parent_data parent_,
	string const &text_,
	font::metrics_ptr _font)
	: widget(
			parent_,
			size_policy_t(axis_policy::can_grow,axis_policy::none),
			keyboard_focus::receive),
	  text_(text_),
	  font_(_font),
		mouse_over_(false),
		key_over_(false)
{
	if (!font_)
		font_ = parent_manager().standard_font();

	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("button: no standard font could be set by manager"));
}

sge::gui::dim const sge::gui::widgets::button::size_hint() const
{
	font::font fn(font_,font::drawer_ptr());	

	// NOTE: we have to give text_size a huge rectangle because it won't
	// return a valid rectangle otherwise
	dim const font_dim = math::structure_cast<unit>(
		fn.text_size(text_,math::max_dim<font::unit>()).size());

	return dim(static_cast<unit>(font_dim.w()+2),static_cast<unit>(font_dim.h()+2));
}

void sge::gui::widgets::button::process(events::mouse_enter const &)
{
	mouse_over_ = true;
	parent_manager().invalidate(absolute_area());
}

void sge::gui::widgets::button::process(events::mouse_leave const &)
{
	mouse_over_ = false;
	parent_manager().invalidate(absolute_area());
}

void sge::gui::widgets::button::process(events::mouse_click const &)
{
	clicked();
}

sge::gui::key_handling::type sge::gui::widgets::button::process(
	events::key const &k)
{
	if (k.value().key().code() == input::kc::key_return)
	{
		clicked();
		return key_handling::ignore;
	}
	return key_handling::process;
}

void sge::gui::widgets::button::process(events::keyboard_enter const &)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_enter"));
	key_over_ = true;
	parent_manager().invalidate(absolute_area());
}

void sge::gui::widgets::button::process(events::keyboard_leave const &)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_leave"));
	key_over_ = false;
	parent_manager().invalidate(absolute_area());
}
