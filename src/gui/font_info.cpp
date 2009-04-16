#include <sge/gui/font_info.hpp>

sge::gui::font_info::font_info(
	font::metrics_ptr const _metrics,
	sge::gui::color const &_color)
:
	metrics_(_metrics),
	color_(_color)
{
}

sge::font::metrics_ptr const sge::gui::font_info::metrics() const
{
	return metrics_;
}

sge::gui::color const sge::gui::font_info::color() const
{
	return color_;
}
