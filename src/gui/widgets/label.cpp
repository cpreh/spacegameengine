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
	true);
}

sge::gui::widgets::label::label(
	parent_data const &_parent,
	parameters _params,
	string const &_text,
	sge::font::align_h::type _align_h,
	sge::font::align_v::type _align_v,
	boost::optional<dim> _static_size,
	font::metrics_ptr _font,
	sge::gui::color const &_color)
	: widget(
			_parent,
			_params.size_policy(
				size_policy_t(
					axis_policy::none,
					axis_policy::none))),
	  text_(_text),
		align_h_(_align_h),
		align_v_(_align_v),
		static_size_(_static_size),
	  font_(_font),
		color_(_color)
{
	if (!font_)
		font_ = parent_manager().standard_font();
	
	SGE_ASSERT_MESSAGE(font_,SGE_TEXT("label: no standard font could be set by manager"));
}

sge::font::metrics_ptr const sge::gui::widgets::label::font() const 
{ 
	return font_; 
}

sge::gui::color const sge::gui::widgets::label::color() const 
{ 
	return color_; 
}

sge::string const sge::gui::widgets::label::text() const 
{ 
	return text_; 
}

sge::font::align_h::type sge::gui::widgets::label::align_h() const 
{ 
	return align_h_; 
}

sge::font::align_v::type sge::gui::widgets::label::align_v() const 
{ 
	return align_v_; 
}

void sge::gui::widgets::label::text(
	string const &_text) 
{ 
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("setting text to: ")
		        << _text);
	text_ = _text; 
	invalidate(*this);
}

boost::optional<sge::gui::dim> const
sge::gui::widgets::label::static_size() const 
{ 
	return static_size_; 
}
