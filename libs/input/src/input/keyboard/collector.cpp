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


#include <sge/input/processor.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event_fwd.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/manager.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event_fwd.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::input::keyboard::collector::collector(
	sge::input::processor &_processor
)
:
	manager_(
		_processor,
		sge::input::keyboard::discover_callback{
			[](
				sge::input::keyboard::discover_event const &
			){}
		},
		sge::input::keyboard::remove_callback{
			[](
				sge::input::keyboard::remove_event const &
			){}
		},
		sge::input::keyboard::manager::key_callback{
			std::bind(
				&sge::input::keyboard::collector::key_callback_internal,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		}
	),
	key_signal_()
{
}
FCPPT_PP_POP_WARNING

sge::input::keyboard::collector::~collector()
{
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::key_callback(
	sge::input::keyboard::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

void
sge::input::keyboard::collector::key_callback_internal(
	sge::input::keyboard::device &,
	sge::input::keyboard::key_event const &_event
)
{
	key_signal_(
		_event
	);
}
