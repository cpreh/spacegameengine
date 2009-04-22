#include <sge/gui/widgets/buttons/base.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/events/mouse_click.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/log.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_code.hpp>
#include <sge/math/rect_impl.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::widgets::global_log(),
	SGE_TEXT("buttons::base"),
	false);
}


bool
sge::gui::widgets::buttons::base::mouse_over() const
{
	return mouse_over_;
}
	
bool
sge::gui::widgets::buttons::base::key_over() const
{
	return key_over_;
}

void sge::gui::widgets::buttons::base::process(events::mouse_enter const &)
{
	mouse_over_ = true;
	parent_manager().dirty(*this,rect(point::null(),size()));
}

void sge::gui::widgets::buttons::base::process(events::mouse_leave const &)
{
	mouse_over_ = false;
	parent_manager().dirty(*this,rect(point::null(),size()));
}

void sge::gui::widgets::buttons::base::process(events::mouse_click const &c)
{
	if (c.value().value())
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
	parent_manager().dirty(*this,rect(point::null(),size()));
}

void sge::gui::widgets::buttons::base::process(events::keyboard_leave const &)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_leave"));
	key_over_ = false;
	parent_manager().dirty(*this,rect(point::null(),size()));
}

sge::signal::auto_connection sge::gui::widgets::buttons::base::register_clicked(
	clicked_fn const &_clicked)
{
	return clicked_.connect(_clicked);
}

sge::gui::widgets::buttons::base::~base() {}

sge::gui::widgets::buttons::base::base(
	parent_data const &_parent,
	parameters _params)
:
	widgets::base(
		_parent,
		_params
			.keyboard_focus(
				keyboard_focus::receive)),
	mouse_over_(false),
	key_over_(false)
{
}
