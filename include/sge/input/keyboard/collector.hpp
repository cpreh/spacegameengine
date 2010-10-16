/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_INPUT_KEYBOARD_COLLECTOR_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_COLLECTOR_HPP_INCLUDED

#include <sge/input/keyboard/collector_fwd.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/input/keyboard/key_function.hpp>
#include <sge/input/keyboard/key_repeat_function.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_fwd.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <map>

namespace sge
{
namespace input
{
namespace keyboard
{

class collector
{
	FCPPT_NONCOPYABLE(
		collector
	)
public:
	SGE_SYMBOL
	explicit collector(
		input::processor_ptr
	);

	SGE_SYMBOL
	~collector();

	SGE_SYMBOL
	fcppt::signal::auto_connection
	key_callback(
		keyboard::key_callback const &
	);

	SGE_SYMBOL
	fcppt::signal::auto_connection
	key_repeat_callback(
		keyboard::key_repeat_callback const &
	);
private:
	void
	key_callback(
		keyboard::key_event const &
	);

	void
	key_repeat_callback(
		keyboard::key const &
	);

	void
	discover_callback(
		keyboard::device_ptr
	);

	void
	remove_callback(
		keyboard::device_ptr
	);

	typedef fcppt::signal::object<
		keyboard::key_function
	> key_signal;

	typedef fcppt::signal::object<
		keyboard::key_repeat_function
	> key_repeat_signal;

	typedef boost::ptr_map<
		keyboard::device_ptr,
		fcppt::signal::connection_manager
	> keyboard_map;

	fcppt::signal::connection_manager const connections_;

	key_signal signal_;

	key_repeat_signal repeat_signal_;

	keyboard_map devices_;
};

}
}
}

#endif
