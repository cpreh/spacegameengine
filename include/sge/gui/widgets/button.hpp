#ifndef SGE_GUI_WIDGETS_BUTTON_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BUTTON_HPP_INCLUDED

#include "../widget.hpp"
#include "../../export.hpp"
#include "../../font/metrics_fwd.hpp"
#include <boost/signals.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL button : public widget
{
	public:
	SGE_SYMBOL button(
		parent_data,
		string const &,
		font::metrics_ptr = font::metrics_ptr());

	SGE_SYMBOL dim const size_hint() const;
	dim const minimum_size() const { return size_hint(); }
	string const text() const { return text_; }
	sge::font::metrics_ptr const font() const { return font_; }
	bool mouse_over() const { return mouse_over_; }
	bool key_over() const { return key_over_; }
	SGE_SYMBOL void process(events::mouse_enter const &);
	SGE_SYMBOL void process(events::mouse_leave const &);
	SGE_SYMBOL void process(events::mouse_click const &);
	SGE_SYMBOL void process(events::keyboard_enter const &);
	SGE_SYMBOL void process(events::key const &);
	SGE_SYMBOL void process(events::keyboard_leave const &);

	// signals
	boost::signal<void ()> clicked;
	private:
	string text_;
	font::metrics_ptr font_;
	bool mouse_over_;
	bool key_over_;
};
}
}
}

#endif
