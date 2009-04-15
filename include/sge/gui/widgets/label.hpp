#ifndef SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED
#define SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED

#include <sge/gui/widgets/base.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/color.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/align_v.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <boost/optional.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL label : public base
{
public:
	SGE_GUI_SYMBOL label(
		parent_data const &,
		parameters,
		string const &,
		sge::font::align_h::type = sge::font::align_h::left,
		sge::font::align_v::type = sge::font::align_v::top,
		boost::optional<dim> static_size = boost::none,
		font::metrics_ptr = font::metrics_ptr(),
		sge::gui::color const & = renderer::colors::black());
	
	SGE_GUI_SYMBOL font::metrics_ptr const font() const;
	SGE_GUI_SYMBOL sge::gui::color const color() const;
	SGE_GUI_SYMBOL string const text() const;
	SGE_GUI_SYMBOL sge::font::align_h::type align_h() const;
	SGE_GUI_SYMBOL sge::font::align_v::type align_v() const;
	SGE_GUI_SYMBOL void text(string const &_text);
	SGE_GUI_SYMBOL boost::optional<dim> const static_size() const;
	private:
	string text_;
	sge::font::align_h::type align_h_;
	sge::font::align_v::type align_v_;
	boost::optional<dim> static_size_;
	font::metrics_ptr font_;
	sge::gui::color color_;
};
}
}
}

#endif
