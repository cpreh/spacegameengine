#ifndef SGE_GUI_DETAIL_MANAGERS_KEYBOARD_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_KEYBOARD_HPP_INCLUDED

#include "../submanager.hpp"
#include "../../widget_fwd.hpp"
#include "../../keyboard_focus.hpp"
#include "../../../input/system_fwd.hpp"
#include "../../../input/modifier/filter.hpp"
#include "../../../input/modifier/states.hpp"
#include "../../../input/key_pair_fwd.hpp"
#include "../../../input/key_type.hpp"
#include "../../../signals/scoped_connection.hpp"
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
	signals::scoped_connection ic;
	signals::scoped_connection irc;

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
