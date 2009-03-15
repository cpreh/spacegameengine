#ifndef SGE_GUI_WIDGETS_BUTTONS_TEXT_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BUTTONS_TEXT_HPP_INCLUDED

#include <sge/gui/widgets/buttons/base.hpp>
#include <sge/export.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
namespace buttons
{
class SGE_CLASS_SYMBOL text : public base
{
	public:
	SGE_SYMBOL text(
		parent_data const &,
		parameters,
		string const &,
		font::metrics_ptr = font::metrics_ptr());

	// TODO: move to cpp file
	string const caption() const { return caption_; }
	font::metrics_ptr const font() const { return font_; }
	private:
	string caption_;
	font::metrics_ptr font_;
};
}
}
}
}

#endif
