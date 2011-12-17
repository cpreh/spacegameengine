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


#include <sge/x11input/device/event_data.hpp>
#include <sge/x11input/device/event_demuxer.hpp>
#include <sge/x11input/device/hierarchy_event.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/raw_event.hpp>
#include <sge/x11input/device/select_events.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/unregister/base_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/type_traits/generate_has_member_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <boost/utility/enable_if.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


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
	awl::backends::x11::system::event::processor &_system_processor,
	awl::backends::x11::system::event::opcode const &_opcode,
	awl::backends::x11::window::instance const &_window,
	x11input::device::demuxer_enabled const _enabled
)
:
	system_processor_(
		_system_processor
	),
	opcode_(
		_opcode
	),
	window_(
		_window
	),
	signals_(),
	active_(
		_enabled.get()
	)
{
}

template<
	typename Event
>
sge::x11input::device::event_demuxer<Event>::~event_demuxer()
{
	FCPPT_ASSERT_ERROR(
		signals_.empty()
	);

	FCPPT_ASSERT_ERROR(
		connections_.empty()
	);
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
		connections_.find(
			_type
		)
		== connections_.end()
	)
		fcppt::container::ptr::insert_unique_ptr_map(
			connections_,
			_type,
			system_processor_.register_callback(
				opcode_,
				_type,
				std::tr1::bind(
					&event_demuxer::on_event,
					this,
					std::tr1::placeholders::_1
				)
			)
		);

	event_pair const pair(
		_type,
		_id
	);

	typename signal_map::iterator it(
		signals_.find(
			pair
		)
	);

	if(
		it == signals_.end()
	)
	{
		it =
			fcppt::container::ptr::insert_unique_ptr_map(
				signals_,
				pair,
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
sge::x11input::device::event_demuxer<Event>::active(
	bool const _active
)
{
	active_ = _active;
}

template<
	typename Event
>
void
sge::x11input::device::event_demuxer<Event>::on_event(
	awl::backends::x11::system::event::object const &_event
)
{
	// Ingore everything while not in our window
	if(
		!active_
	)
		return;

	x11input::device::event_data const cookie(
		window_.display(),
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
		event_pair(
			awl::backends::x11::system::event::type(
				device_event.evtype
			),
			::device_id(
				device_event
			)
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
	typename signal_map::iterator const it(
		signals_.find(
			event_pair(
				_type,
				_id
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		it
		!= signals_.end()
	);

	if(
		it->second->empty()
	)
	{
		signals_.erase(
			it
		);

		x11input::device::select_events(
			window_,
			_id,
			_type,
			false
		);

		if(
			!this->signal_remains(
				_type
			)
		)
			FCPPT_ASSERT_ERROR(
				connections_.erase(
					_type
				)
				== 1u
			);
	}
}

template<
	typename Event
>
bool
sge::x11input::device::event_demuxer<Event>::signal_remains(
	awl::backends::x11::system::event::type const _type
) const
{
	return
		signals_.lower_bound(
			event_pair(
				_type,
				x11input::device::id(
					std::numeric_limits<
						x11input::device::id::value_type
					>::min()
				)
			)
		)
		!= signals_.upper_bound(
			event_pair(
				_type,
				x11input::device::id(
					std::numeric_limits<
						x11input::device::id::value_type
					>::max()
				)
			)
		);
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
