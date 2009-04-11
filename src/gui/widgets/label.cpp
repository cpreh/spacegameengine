#include <sge/gui/widgets/label.hpp>
#include <sge/gui/events/invalid_area.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/log.hpp>
#include <sge/assert.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::widgets::global_log(),
	SGE_TEXT("label"),
	false);
}

sge::gui::widgets::label::label(
	parent_data const &_parent,
	parameters _params,
	string const &_text,
	boost::optional<dim> _static_size,
	font::metrics_ptr _font)
	: widget(
			_parent,
			_params.size_policy(
				size_policy_t(
					axis_policy::none,
					axis_policy::none))),
	  text_(_text),
		static_size_(_static_size),
	  font_(_font)
{
	if (!font_)
		font_ = parent_manager().standard_font();
	
	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("label: no standard font could be set by manager"));
}

sge::font::metrics_ptr const sge::gui::widgets::label::font() const 
{ 
	return font_; 
}

sge::string const sge::gui::widgets::label::text() const 
{ 
	return text_; 
}

void sge::gui::widgets::label::text(
	string const &_text) 
{ 
	text_ = _text; 
	compile();
}

boost::optional<sge::gui::dim> const
sge::gui::widgets::label::static_size() const 
{ 
	return static_size_; 
}
