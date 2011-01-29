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


#include "../event_demuxer.hpp"
#include "../event_data.hpp"
#include "../id.hpp"
#include "../hierarchy_event.hpp"
#include "../select_events.hpp"
#include "../raw_event.hpp"
#include "../window_event.hpp"
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/signal/unregister/base_impl.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/type_traits/generate_has_member_function.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/foreach.hpp>
#include <X11/extensions/XInput2.h>

namespace
{

FCPPT_TYPE_TRAITS_GENERATE_HAS_MEMBER_FUNCTION(
	deviceid
);

template<
	typename T
>
struct has_deviceid_wrapped
:
::has_deviceid<
	T,
	int T::*
>
{
};

template<
	typename T
>
typename boost::disable_if<
	::has_deviceid_wrapped<
		T
	>,
	sge::x11input::device::id
>::type const
device_id(
	T const &
)
{
	return
		sge::x11input::device::id(
			XIAllDevices
		);
}

template<
	typename T
>
typename boost::enable_if<
	::has_deviceid_wrapped<
		T
	>,
	sge::x11input::device::id
>::type const
device_id(
	T const &_event
)
{
	return
		sge::x11input::device::id(
			_event.deviceid
		);
}

}

template<
	typename Event
>
sge::x11input::device::event_demuxer<Event>::event_demuxer(
	awl::backends::x11::system::event::processor_ptr const _system_processor,
	awl::backends::x11::system::event::opcode const &_opcode,
	awl::backends::x11::window::instance_ptr const _window
)
:
	system_processor_(_system_processor),
	opcode_(_opcode),
	window_(_window),
	signals_()
{
}

template<
	typename Event
>
sge::x11input::device::event_demuxer<Event>::~event_demuxer()
{
}

template<
	typename Event
>
fcppt::signal::auto_connection
sge::x11input::device::event_demuxer<Event>::register_callback(
	awl::backends::x11::system::event::type const &_type,
	x11input::device::id const &_id,
	callback const &_callback
)
{
	if(
		connections_.count(
			_type
		) == 0u
	)
		fcppt::container::ptr::insert_unique_ptr_map(
			connections_,
			_type,
			system_processor_->register_callback(
				opcode_,
				_type,
				std::tr1::bind(
					&event_demuxer::on_event,
					this,
					std::tr1::placeholders::_1
				)
			)
		);
	
	event_signal_map &inner_map(
		signals_[
			_id
		]
	);

	typename event_signal_map::iterator it(
		inner_map.find(
			_type
		)
	);

	if(
		it == inner_map.end()
	)
	{
		it =
			fcppt::container::ptr::insert_unique_ptr_map(
				inner_map,
				_type,
				fcppt::make_unique_ptr<
					signal
				>()
			).first;

		x11input::device::select_events(
			window_,
			_id,
			_type,
			true
		);
	}

	return
		it->second->connect(
			_callback,
			std::tr1::bind(
				&event_demuxer::unregister,
				this,
				_id,
				_type
			)
		);
}

template<
	typename Event
>
void
sge::x11input::device::event_demuxer<Event>::on_event(
	awl::backends::x11::system::event::object const &_event
)
{
	x11input::device::event_data const cookie(
		window_->display(),
		_event
	);

	typedef typename Event::value_type xi_event;

	xi_event const &device_event(
		*static_cast<
			xi_event const *
		>(
			cookie.data()
		)
	);

	signals_[
		::device_id(
			device_event
		)
	][
		awl::backends::x11::system::event::type(
			device_event.evtype
		)
	](
		Event(
			device_event
		)
	);
}

template<
	typename Event
>
void
sge::x11input::device::event_demuxer<Event>::unregister(
	device::id const &_id,
	awl::backends::x11::system::event::type const _type
)
{
	typename device_signal_map::iterator const device_it(
		signals_.find(
			_id
		)
	);

	assert(
		device_it
		!= signals_.end()
	);

	event_signal_map &inner_map(
		*device_it->second
	);

	typename event_signal_map::iterator const signal_it(
		inner_map.find(
			_type
		)
	);

	assert(
		signal_it
		!= inner_map.end()
	);

	if(
		signal_it->second->empty()
	)
	{
		inner_map.erase(
			signal_it
		);

		x11input::device::select_events(
			window_,
			_id,
			_type,
			false
		);

		if(
			inner_map.empty()
		)
			signals_.erase(
				device_it
			);

		// TODO: remove a connection if there is no signal for the event left!
	}
}

template class
sge::x11input::device::event_demuxer<
	sge::x11input::device::window_event
>;

template class
sge::x11input::device::event_demuxer<
	sge::x11input::device::raw_event
>;

template class
sge::x11input::device::event_demuxer<
	sge::x11input::device::hierarchy_event
>;
