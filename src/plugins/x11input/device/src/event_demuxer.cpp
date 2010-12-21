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


#include "../device::event_demuxer.hpp"
#include "../event_id_container.hpp"
#include "../select_events.hpp"
#include <fcppt/algorithm/map.hpp>
#include <fcppt/signal/unregister/base_impl.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/tr1/bind.hpp>

sge::x11input::device::event_demuxer::event_demuxer(
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

sge::x11input::device::event_demuxer::~event_demuxer()
{
}

fcppt::signal::auto_connection
sge::x11input::device::event_demuxer::register_callback(
	awl::backends::x11::system::event::type const &_type,
	x11input::device::id const &_id,
	x11input::device_callback const &_callback
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
			system_processor_->connect(
				opcode_,
				_type,
				std::tr1::bind(
					&event_demuxer::on_event,
					this,
					std::tr1::placeholders::_1
				)
			)
		);

	signal_map::key_type const key(
		std::make_pair(
			_id,
			_type
		)
	);

	signal_map::iterator it(
		signals_.find(
			key
		)
	);

	if(
		it == signals_.end()
	)
	{
		it =
			fcppt::container::ptr::insert_unique_ptr_map(
				signals_,
				key,
				fcppt::make_unqiue_ptr<
					signal
				>()
			);

		this->select_events(
			_id
		);
	}

	return
		it->second->connect(
			_callback,
			std::tr1::bind(
				&event_demuxer::unregister,
				this,
				key.first,
				key.second
			)
		);
}

void
sge::x11input::device::event_demuxer::on_event(
	awl::backends::x11::system::event::object const &_event
)
{
	x11input::event_data const cookie(
		window_->display(),
		_event
	);

	XIDeviceEvent const &device_event(
		*static_cast<
			XIDeviceEvent const *
		>(
			cookie.data()
		)
	);

	signals_[
		std::make_pair(
			device::id(
				device_event.deviceid
			),
			awl::backends::x11::system::event::type(
				device_event.type
			)
		)
	](
		device::event(
			device_event
		)
	);
}

void
sge::x11input::device::event_demuxer::unregister(
	device::id const &_id,
	awl::backends::x11::system::event::type const _type
)
{
	signal_map::key_type const key(
		_id,
		_type
	);

	if(
		signals_[
			_key
		].empty()
	)
	{
		singals_.erase(
			_key
		);

		// TODO: remove a connection if there is no signal for the event left!
		this->select_events(
			_id
		);
	}
}

void
sge::x11input::device::event_demuxer::select_events(
	device::id const &_id
)
{
	
	x11input::select_events(
		param_.window(),
		param_.device_id(),
		fcppt::algorithm::map<
			x11input::event_id_container
		>(
			event_counts_,
			std::tr1::bind(
				&event_count_map::value_type::type,
				std::tr1::placeholders::_1
			)
		)
	);
}
