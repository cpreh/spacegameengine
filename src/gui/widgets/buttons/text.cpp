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
	false);
}

sge::gui::widgets::buttons::text::text(
	parent_data const &_parent,
	parameters _params,
	string const &_caption,
	font::metrics_ptr _font)
	: base(
			_parent,
			_params
				.size_policy(
					sge::gui::size_policy(
						axis_policy::can_grow,
						axis_policy::none))),
	  caption_(_caption),
	  font_(_font)
{
	if (!font_)
		font_ = parent_manager().standard_font();
	
	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("button: no standard font could be set by manager"));
}
