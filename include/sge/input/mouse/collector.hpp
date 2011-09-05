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


#ifndef SGE_INPUT_MOUSE_COLLECTOR_HPP_INCLUDED
#define SGE_INPUT_MOUSE_COLLECTOR_HPP_INCLUDED

#include <sge/input/mouse/collector_fwd.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/device_ptr.hpp>
#include <sge/input/mouse/axis_function.hpp>
#include <sge/input/mouse/button_function.hpp>
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/input/mouse/button_event_fwd.hpp>
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
namespace mouse
{

class collector
:
	public mouse::device
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
		mouse::axis_callback const &
	);

	SGE_INPUT_SYMBOL
	fcppt::signal::auto_connection
	button_callback(
		mouse::button_callback const &
	);
private:
	void
	axis_callback_internal(
		mouse::axis_event const &
	);

	void
	button_callback_internal(
		mouse::button_event const &
	);

	void
	discover_callback(
		mouse::device_ptr
	);

	void
	remove_callback(
		mouse::device_ptr
	);

	typedef fcppt::signal::object<
		mouse::axis_function
	> axis_signal;

	typedef fcppt::signal::object<
		mouse::button_function
	> button_signal;

	typedef boost::ptr_map<
		mouse::device_ptr,
		fcppt::signal::connection_manager
	> mouse_map;

	fcppt::signal::connection_manager const connections_;

	axis_signal axis_signal_;

	button_signal button_signal_;

	mouse_map devices_;
};

}
}
}

#endif
