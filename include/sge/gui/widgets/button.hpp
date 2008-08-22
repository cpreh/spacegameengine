#ifndef SGE_GUI_WIDGETS_BUTTON_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BUTTON_HPP_INCLUDED

#include "../widget.hpp"
#include <sge/font/metrics.hpp>
#include <boost/signals.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class button : public widget
{
	public:
	button(
		parent_data,
		string const &,
		font::metrics_ptr = font::metrics_ptr(),
		point const & = point(),
		dim const & = dim());

	// overridden virtuals
	dim minimum_size() const;
	void process(events::invalid_area const &);
	void process(events::mouse_enter const &);
	void process(events::mouse_leave const &);
	void process(events::mouse_click const &);

	// signals
	boost::signal<void ()> clicked;
	private:
	void do_size(dim const &);
	void do_pos(point const &);
	void do_compile();

	string text_;
	font::metrics_ptr font_;
	bool mouse_over;
};
}
}
}

#endif
