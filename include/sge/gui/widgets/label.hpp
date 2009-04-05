#ifndef SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED
#define SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED

#include <sge/gui/widget.hpp>
#include <sge/export.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <boost/optional.hpp>

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
		parent_data const &,
		parameters,
		string const &,
		boost::optional<dim> static_size = boost::none,
		font::metrics_ptr = font::metrics_ptr());
	
	font::metrics_ptr const font() const { return font_; }
	string const text() const { return text_; }
	void text(string const &_text) { text_ = _text; }
	boost::optional<dim> static_size() const { return static_size_; }
	private:
	string text_;
	boost::optional<dim> static_size_;
	font::metrics_ptr font_;
};
}
}
}

#endif
