/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <unordered_map>
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
	typedef std::function<
		void (
			sge::input::keyboard::device &,
			sge::input::keyboard::char_event const &
		)
	> char_callback;

	typedef std::function<
		void (
			sge::input::keyboard::device &,
			sge::input::keyboard::key_event const &
		)
	> key_callback;

	typedef std::function<
		void (
			sge::input::keyboard::device &,
			sge::input::keyboard::key_repeat_event const &
		)
	> key_repeat_callback;

	SGE_INPUT_SYMBOL
	manager(
		sge::input::processor &,
		sge::input::keyboard::discover_callback const &,
		sge::input::keyboard::remove_callback const &,
		char_callback const &,
		key_callback const &,
		key_repeat_callback const &
	);

	SGE_INPUT_SYMBOL
	~manager();

	typedef std::unordered_map<
		sge::input::keyboard::device *,
		fcppt::signal::connection_manager
	> keyboard_map;

	SGE_INPUT_SYMBOL
	keyboard_map const &
	devices() const;
private:
	void
	discover(
		sge::input::keyboard::discover_event const &
	);

	void
	remove(
		sge::input::keyboard::remove_event const &
	);

	keyboard_map devices_;

	sge::input::keyboard::discover_callback const discover_callback_;

	sge::input::keyboard::remove_callback const remove_callback_;

	char_callback const char_callback_;

	key_callback const key_callback_;

	key_repeat_callback const key_repeat_callback_;

	fcppt::signal::connection_manager const connections_;
};

}
}
}

#endif
