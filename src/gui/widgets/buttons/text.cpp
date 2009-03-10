#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/log.hpp>
#include <sge/input/key_type.hpp>
#include <sge/assert.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::widgets::global_log(),
	SGE_TEXT("buttons::text"),
	true);
}

sge::gui::widgets::buttons::text(
	parent_data const &_parent,
	parameters _params,
	string const &_text,
	font::metrics_ptr _font)
	: widget(
			_parent,
			_params
				.size_policy(
					size_policy_t(
						axis_policy::can_grow,
						axis_policy::none))),
	  text_(_text),
	  font_(_font)
{
	if (!font_)
		font_ = parent_manager().standard_font();
	
	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("button: no standard font could be set by manager"));
}
