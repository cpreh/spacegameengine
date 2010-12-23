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


#ifndef SGE_X11INPUT_DEVICE_EVENT_DEMUXER_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_EVENT_DEMUXER_HPP_INCLUDED

#include "event_demuxer_fwd.hpp"
#include "id.hpp"
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/system/event/processor_ptr.hpp>
#include <awl/backends/x11/system/event/type.hpp>
#include <awl/backends/x11/system/event/object_fwd.hpp>
#include <awl/backends/x11/window/instance_ptr.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/unregister/base_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sge
{
namespace x11input
{
namespace device
{

template<
	typename Event
>
class event_demuxer
{
	FCPPT_NONCOPYABLE(
		event_demuxer
	)

	typedef void
	signature(
		Event const &
	);
public:
	explicit event_demuxer(
		awl::backends::x11::system::event::processor_ptr,
		awl::backends::x11::system::event::opcode const &,
		awl::backends::x11::window::instance_ptr
	);

	~event_demuxer();

	typedef fcppt::function::object<
		signature
	> callback;

	fcppt::signal::auto_connection
	register_callback(
		awl::backends::x11::system::event::type const &,
		x11input::device::id const &,
		callback const &
	);
private:
	void
	on_event(
		awl::backends::x11::system::event::object const &
	);

	void
	unregister(
		device::id const &,
		awl::backends::x11::system::event::type
	);

	void
	select_events(
		device::id const &
	);

	typedef fcppt::signal::object<
		signature,
		fcppt::signal::unregister::base
	> signal;

	typedef boost::ptr_map<
		awl::backends::x11::system::event::type,
		signal
	> event_signal_map;

	typedef boost::ptr_map<
		x11input::device::id,
		event_signal_map
	> device_signal_map;

	typedef boost::ptr_map<
		awl::backends::x11::system::event::type,
		fcppt::signal::auto_connection::element_type
	> connection_map;

	awl::backends::x11::system::event::processor_ptr const system_processor_;

	awl::backends::x11::system::event::opcode const opcode_;

	awl::backends::x11::window::instance_ptr const window_;

	connection_map connections_;

	device_signal_map signals_;
};

}
}
}

#endif
