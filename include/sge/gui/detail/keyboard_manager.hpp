#ifndef SGE_GUI_KEYBOARD_MANAGER_HPP_INCLUDED
#define SGE_GUI_KEYBOARD_MANAGER_HPP_INCLUDED

#include "../widget_fwd.hpp"
#include "../keyboard_focus.hpp"
#include "../../input/system_fwd.hpp"
#include "../../input/key_pair_fwd.hpp"
#include "../../signals/scoped_connection.hpp"
#include <boost/optional.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
class keyboard_manager
{
	public:
	keyboard_manager(input::system_ptr);
	void add(widget &);
	void request_focus(widget &);
	void remove(widget &);
	void cycle_focus();
	void keyboard_focus(widget &,keyboard_focus::type);
	private:
	typedef boost::ptr_list<widget,boost::view_clone_allocator> widget_container;

	widget_container widgets;
	boost::optional<widget_container::iterator> focus;
	signals::scoped_connection ic;

	void input_callback(input::key_pair const &);
	void switch_focus(widget_container::iterator);
};
}
}
}

#endif
