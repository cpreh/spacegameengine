#ifndef SGE_GUI_DETAIL_MANAGERS_KEYBOARD_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_KEYBOARD_HPP_INCLUDED

#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/modifier/filter.hpp>
#include <sge/input/modifier/states.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/input/key_type.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <boost/optional.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
namespace managers
{
class keyboard : public submanager
{
	public:
	keyboard(input::system_ptr);
	void add(widget &);
	void activation(widget &,activation_state::type);
	void request_focus(widget &);
	void remove(widget &);
	void cycle_focus();
	void keyboard_focus(widget &,keyboard_focus::type);
	private:
	typedef boost::ptr_list<widget,boost::view_clone_allocator> widget_container;

	input::modifier::filter input_filter;
	widget_container widgets;
	boost::optional<widget_container::iterator> focus;
	signal::scoped_connection const
		ic,
		irc;

	void input_callback(
		input::key_pair const &,
		input::modifier::states const &,
		bool);
	void repeat_callback(
		input::key_type const &,
		input::modifier::states const &);
	void switch_focus(widget_container::iterator);
};
}
}
}
}

#endif
