#ifndef SGE_GUI_WIDGETS_BUTTONS_BASE_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BUTTONS_BASE_HPP_INCLUDED

#include <sge/gui/widget.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/signal/object.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
namespace buttons
{
class SGE_CLASS_SYMBOL base : public widget
{
	public:
	bool mouse_over() const { return mouse_over_; }
	bool key_over() const { return key_over_; }

	SGE_SYMBOL void process(events::mouse_enter const &);
	SGE_SYMBOL void process(events::mouse_leave const &);
	SGE_SYMBOL void process(events::mouse_click const &);
	SGE_SYMBOL void process(events::keyboard_enter const &);
	SGE_SYMBOL key_handling::type process(events::key const &);
	SGE_SYMBOL void process(events::keyboard_leave const &);

	typedef boost::function<void ()> clicked_fn;
	SGE_SYMBOL signal::auto_connection register_clicked(
		clicked_fn const &);
	
	SGE_SYMBOL ~base();
	private:
	bool mouse_over_;
	bool key_over_;
	sge::signal::object<void ()> clicked_;

	protected:
	SGE_SYMBOL base(
		parent_data const &,
		parameters);
};
}
}
}
}

#endif
