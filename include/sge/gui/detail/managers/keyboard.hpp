/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GUI_DETAIL_MANAGERS_KEYBOARD_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_KEYBOARD_HPP_INCLUDED

#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/input/modifier/filter.hpp>
#include <sge/input/modifier/states.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/optional.hpp>
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
	explicit keyboard(
		input::keyboard::device_ptr
	);

	void add(widgets::base &);
	void activation(widgets::base &,activation_state::type);
	void request_focus(widgets::base &);
	void remove(widgets::base &);
	void cycle_focus();
	void keyboard_focus(widgets::base &,keyboard_focus::type);
private:
	typedef boost::ptr_list<
		widgets::base,
		boost::view_clone_allocator
		> widget_container;

	input::modifier::filter input_filter;
	widget_container widgets;
	fcppt::optional<widget_container::iterator> focus;
	fcppt::signal::scoped_connection const
		ic,
		irc;

	void input_callback(
		input::keyboard::key_event const &,
		input::modifier::states const &,
		bool);
	void repeat_callback(
		input::keyboard::key_repeat_event const &,
		input::modifier::states const &);
	void switch_focus(widget_container::iterator);
};
}
}
}
}

#endif
