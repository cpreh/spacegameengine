#ifndef SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED
#define SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED

#include <sge/gui/widget.hpp>
#include <sge/gui/export.hpp>
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
	SGE_GUI_SYMBOL label(
		parent_data const &,
		parameters,
		string const &,
		boost::optional<dim> static_size = boost::none,
		font::metrics_ptr = font::metrics_ptr());
	
	SGE_GUI_SYMBOL font::metrics_ptr const font() const;
	SGE_GUI_SYMBOL string const text() const;
	SGE_GUI_SYMBOL void text(string const &_text);
	SGE_GUI_SYMBOL boost::optional<dim> const static_size() const;
private:
	string text_;
	boost::optional<dim> static_size_;
	font::metrics_ptr font_;
};
}
}
}

#endif
