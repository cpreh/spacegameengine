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


#ifndef SGE_INPUT_JOYPAD_COLLECTOR_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_COLLECTOR_HPP_INCLUDED

#include <sge/input/joypad/collector_fwd.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/device_ptr.hpp>
#include <sge/input/joypad/axis_function.hpp>
#include <sge/input/joypad/button_function.hpp>
#include <sge/input/joypad/axis_callback.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/axis_event_fwd.hpp>
#include <sge/input/joypad/button_event_fwd.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/input/symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace input
{
namespace joypad
{

class collector
:
	public joypad::device
{
	FCPPT_NONCOPYABLE(
		collector
	);
public:
	SGE_INPUT_SYMBOL
	explicit collector(
		input::processor_ptr
	);

	SGE_INPUT_SYMBOL
	~collector();

	SGE_INPUT_SYMBOL
	fcppt::signal::auto_connection
	axis_callback(
		joypad::axis_callback const &
	);

	SGE_INPUT_SYMBOL
	fcppt::signal::auto_connection
	button_callback(
		joypad::button_callback const &
	);
private:
	void
	axis_callback_internal(
		joypad::axis_event const &
	);

	void
	button_callback_internal(
		joypad::button_event const &
	);

	void
	discover_callback(
		joypad::device_ptr
	);

	void
	remove_callback(
		joypad::device_ptr
	);

	typedef fcppt::signal::object<
		joypad::axis_function
	> axis_signal;

	typedef fcppt::signal::object<
		joypad::button_function
	> button_signal;

	typedef boost::ptr_map<
		joypad::device_ptr,
		fcppt::signal::connection_manager
	> joypad_map;

	fcppt::signal::connection_manager const connections_;

	axis_signal axis_signal_;

	button_signal button_signal_;

	joypad_map devices_;
};

}
}
}

#endif
