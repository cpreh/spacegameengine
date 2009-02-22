#ifndef SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED
#define SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED

#include <sge/gui/widget.hpp>
#include <sge/export.hpp>
#include <sge/font/metrics_fwd.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL label : public widget
{
	public:
	SGE_SYMBOL label(
		parent_data,
		string const &,
		font::metrics_ptr = font::metrics_ptr());
	
	font::metrics_ptr const font() const { return font_; }
	string const text() const { return text_; }
	private:
	string text_;
	font::metrics_ptr font_;
};
}
}
}

#endif
