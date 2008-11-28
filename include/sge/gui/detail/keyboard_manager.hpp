#ifndef SGE_GUI_KEYBOARD_MANAGER_HPP_INCLUDED
#define SGE_GUI_KEYBOARD_MANAGER_HPP_INCLUDED

#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <boost/optional.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
class keyboard_manager
{
	public:
	keyboard_manager(sge::input::system_ptr);
	void widget_add(widget &);
	void request_focus(widget &);
	void widget_remove(widget &);
	void cycle_focus();
	void input_callback(sge::input::key_pair const &);
	void keyboard_focus(widget &,keyboard_focus::type);
	private:
	typedef std::list<widget *> widget_container;

	widget_container widgets;
	boost::optional<widget_container::iterator> focus;
	sge::signals::scoped_connection ic;

	void switch_focus(widget_container::iterator);
};
}
}
}

#endif
