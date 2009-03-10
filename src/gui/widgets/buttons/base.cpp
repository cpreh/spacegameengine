#include <sge/gui/widgets/buttons/base.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/log.hpp>
#include <sge/input/key_type.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::widgets::global_log(),
	SGE_TEXT("buttons::base"),
	true);
}

sge::gui::widgets::buttons::base(
	parent_data const &_parent,
	parameters _params)
	: widget(
			_parent,
			_params
				.keyboard_focus(
					keyboard_focus::receive)),
		mouse_over_(false),
		key_over_(false)
{
}

void sge::gui::widgets::buttons::base::process(events::mouse_enter const &)
{
	mouse_over_ = true;
	parent_manager().invalidate(*this,absolute_area());
}

void sge::gui::widgets::buttons::base::process(events::mouse_leave const &)
{
	mouse_over_ = false;
	parent_manager().invalidate(*this,absolute_area());
}

void sge::gui::widgets::buttons::base::process(events::mouse_click const &)
{
	clicked_();
}

sge::gui::key_handling::type sge::gui::widgets::buttons::base::process(
	events::key const &k)
{
	if (k.value().key().code() == input::kc::key_return)
	{
		clicked_();
		return key_handling::ignore;
	}
	return key_handling::process;
}

void sge::gui::widgets::buttons::base::process(events::keyboard_enter const &)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_enter"));
	key_over_ = true;
	parent_manager().invalidate(*this,absolute_area());
}

void sge::gui::widgets::buttons::base::process(events::keyboard_leave const &)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_leave"));
	key_over_ = false;
	parent_manager().invalidate(*this,absolute_area());
}

sge::signals::connection const sge::gui::widgets::buttons::base::register_clicked(
	clicked_fn const &_clicked)
{
	return clicked_.connect(_clicked);
}
