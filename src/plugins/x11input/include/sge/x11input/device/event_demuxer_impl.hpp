/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_X11INPUT_DEVICE_EVENT_DEMUXER_IMPL_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_EVENT_DEMUXER_IMPL_HPP_INCLUDED

#include <sge/x11input/device/demuxer_enabled.hpp>
#include <sge/x11input/device/event_data.hpp>
#include <sge/x11input/device/event_demuxer_decl.hpp>
#include <sge/x11input/device/event_deviceid.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/select_events.hpp>
#include <awl/backends/x11/system/event/callback.hpp>
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/get_or_insert_result.hpp>
#include <fcppt/container/get_or_insert_with_result.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/signal/unregister/base_impl.hpp>
#include <fcppt/signal/unregister/function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <limits>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Event
>
sge::x11input::device::event_demuxer<
	Event
>::event_demuxer(
	awl::backends::x11::system::event::processor &_system_processor,
	awl::backends::x11::system::event::opcode const &_opcode,
	awl::backends::x11::window::object const &_window,
	sge::x11input::device::demuxer_enabled const _enabled
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
	connections_(),
	signals_(),
	active_(
		_enabled.get()
	)
{
}

template<
	typename Event
>
sge::x11input::device::event_demuxer<
	Event
>::~event_demuxer()
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
sge::x11input::device::event_demuxer<
	Event
>::register_callback(
	awl::backends::x11::system::event::type const &_type,
	sge::x11input::device::id const &_id,
	callback const &_callback
)
{
	if(
		connections_.count(
			_type
		)
		==
		0u
	)
		connections_.insert(
			std::make_pair(
				_type,
				system_processor_.register_callback(
					opcode_,
					_type,
					awl::backends::x11::system::event::callback{
						std::bind(
							&event_demuxer::on_event,
							this,
							std::placeholders::_1
						)
					}
				)
			)
		);

	fcppt::container::get_or_insert_result<
		typename
		signal_map::mapped_type &
	> const inserted{
		fcppt::container::get_or_insert_with_result(
			signals_,
			event_pair{
				_type,
				_id
			},
			[](
				event_pair const &
			)
			{
				return
					signal();
			}
		)
	};

	if(
		inserted.inserted()
	)
		sge::x11input::device::select_events(
			window_,
			_id,
			_type,
			true
		);

	return
		inserted.element().connect(
			_callback,
			fcppt::signal::unregister::function{
				std::bind(
					&event_demuxer::unregister,
					this,
					_id,
					_type
				)
			}
		);
}

template<
	typename Event
>
void
sge::x11input::device::event_demuxer<
	Event
>::active(
	bool const _active
)
{
	active_ =
		_active;
}

template<
	typename Event
>
void
sge::x11input::device::event_demuxer<
	Event
>::on_event(
	awl::backends::x11::system::event::object const &_event
)
{
	// Ingore everything while not in our window
	if(
		!active_
	)
		return;

	sge::x11input::device::event_data const cookie(
		window_.display(),
		_event
	);

	typedef typename Event::value_type xi_event;

	xi_event const &device_event(
		*fcppt::cast::from_void_ptr<
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
			sge::x11input::device::event_deviceid(
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
sge::x11input::device::event_demuxer<
	Event
>::unregister(
	sge::x11input::device::id const &_id,
	awl::backends::x11::system::event::type const _type
)
{
	typename signal_map::iterator const it(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::find_opt_iterator(
				signals_,
				event_pair(
					_type,
					_id
				)
			)
		)
	);

	if(
		it->second.empty()
	)
	{
		signals_.erase(
			it
		);

		sge::x11input::device::select_events(
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
				==
				1u
			);
	}
}

template<
	typename Event
>
bool
sge::x11input::device::event_demuxer<
	Event
>::signal_remains(
	awl::backends::x11::system::event::type const _type
) const
{
	return
		signals_.lower_bound(
			event_pair(
				_type,
				sge::x11input::device::id(
					std::numeric_limits<
						x11input::device::id::value_type
					>::min()
				)
			)
		)
		!=
		signals_.upper_bound(
			event_pair(
				_type,
				sge::x11input::device::id(
					std::numeric_limits<
						x11input::device::id::value_type
					>::max()
				)
			)
		);
}

#endif
