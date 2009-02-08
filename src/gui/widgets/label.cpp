#include <sge/gui/widgets/label.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/log.hpp>
#include <sge/assert.hpp>

namespace
{
sge::gui::logger mylogger(sge::gui::widgets::global_log(),SGE_TEXT("label"),true);
}

sge::gui::widgets::label::label(
	parent_data parent_,
	string const &text_,
	font::metrics_ptr _font)
	: widget(
			parent_,
			size_policy_t(axis_policy::can_grow,axis_policy::can_grow),
			keyboard_focus::ignore),
	  text_(text_),
	  font_(_font)
{
	if (!font_)
		font_ = parent_manager().standard_font();
	
	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("label: no standard font could be set by manager"));
}
