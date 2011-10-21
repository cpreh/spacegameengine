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


#include <sge/input/processor_fwd.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_event_fwd.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/collector.hpp>
#include <sge/input/mouse/device_ptr.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <fcppt/text.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::input::mouse::collector::collector(
	input::processor &_processor
)
:
	manager_(
		_processor,
		mouse::discover_callback(),
		mouse::remove_callback(),
		std::tr1::bind(
			&mouse::collector::axis_callback_internal,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		),
		std::tr1::bind(
			&mouse::collector::button_callback_internal,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	),
	info_(
		mouse::axis_info_container(
			mouse::axis_info_container::vector()
		),
		mouse::button_info_container(
			mouse::button_info_container::vector()
		),
		sge::input::info::name(
			FCPPT_TEXT("mouse collector")
		)
	),
	axis_signal_(),
	button_signal_()
{
}
FCPPT_PP_POP_WARNING

sge::input::mouse::collector::~collector()
{
}

fcppt::signal::auto_connection
sge::input::mouse::collector::axis_callback(
	mouse::axis_callback const &_callback
)
{
	return
		axis_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::mouse::collector::button_callback(
	mouse::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

sge::input::mouse::info const &
sge::input::mouse::collector::info() const
{
	return
		info_;
}

void
sge::input::mouse::collector::axis_callback_internal(
	mouse::device_ptr,
	mouse::axis_event const &_event
)
{
	axis_signal_(
		_event
	);
}

void
sge::input::mouse::collector::button_callback_internal(
	mouse::device_ptr,
	mouse::button_event const &_event
)
{
	button_signal_(
		_event
	);
}
