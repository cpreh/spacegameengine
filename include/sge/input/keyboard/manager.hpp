/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_INPUT_KEYBOARD_MANAGER_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_MANAGER_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/symbol.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace input
{
namespace keyboard
{

class manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	typedef fcppt::function::object<
		void (
			keyboard::device_ptr,
			keyboard::char_event const &
		)
	> char_callback;

	typedef fcppt::function::object<
		void (
			keyboard::device_ptr,
			keyboard::key_event const &
		)
	> key_callback;

	typedef fcppt::function::object<
		void (
			keyboard::device_ptr,
			keyboard::key_repeat_event const &
		)
	> key_repeat_callback;

	SGE_INPUT_SYMBOL
	manager(
		input::processor &,
		input::keyboard::discover_callback const &,
		input::keyboard::remove_callback const &,
		char_callback const &,
		key_callback const &,
		key_repeat_callback const &
	);

	SGE_INPUT_SYMBOL
	~manager();

	typedef boost::ptr_map<
		keyboard::device_ptr,
		fcppt::signal::connection_manager
	> keyboard_map;

	SGE_INPUT_SYMBOL
	keyboard_map const &
	devices() const;
private:
	void
	discover(
		input::keyboard::discover_event const &
	);

	void
	remove(
		input::keyboard::remove_event const &
	);

	keyboard_map devices_;

	input::keyboard::discover_callback const discover_callback_;

	input::keyboard::remove_callback const remove_callback_;

	char_callback const char_callback_;

	key_callback const key_callback_;

	key_repeat_callback const key_repeat_callback_;

	fcppt::signal::connection_manager const connections_;
};

}
}
}

#endif
