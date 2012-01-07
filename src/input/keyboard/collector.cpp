/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/input/keyboard/char_callback.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/manager.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::input::keyboard::collector::collector(
	input::processor &_processor
)
:
	manager_(
		_processor,
		keyboard::discover_callback(),
		keyboard::remove_callback(),
		std::tr1::bind(
			&keyboard::collector::char_callback_internal,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		),
		std::tr1::bind(
			&keyboard::collector::key_callback_internal,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		),
		std::tr1::bind(
			&keyboard::collector::key_repeat_callback_internal,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	),
	char_signal_(),
	key_signal_(),
	key_repeat_signal_()
{
}
FCPPT_PP_POP_WARNING

sge::input::keyboard::collector::~collector()
{
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::char_callback(
	keyboard::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::key_callback(
	keyboard::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::key_repeat_callback(
	keyboard::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

sge::input::keyboard::mod_state const
sge::input::keyboard::collector::mod_state() const
{
	keyboard::mod_state ret(
		keyboard::mod_state::null()
	);

	for(
		manager::keyboard_map::const_iterator it(
			manager_.devices().begin()
		);
		it != manager_.devices().end();
		++it
	)
		ret |= it->first->mod_state();

	return ret;
}

void
sge::input::keyboard::collector::char_callback_internal(
	keyboard::device &,
	keyboard::char_event const &_event
)
{
	char_signal_(
		_event
	);
}

void
sge::input::keyboard::collector::key_callback_internal(
	keyboard::device &,
	keyboard::key_event const &_event
)
{
	key_signal_(
		_event
	);
}

void
sge::input::keyboard::collector::key_repeat_callback_internal(
	keyboard::device &,
	keyboard::key_repeat_event const &_event
)
{
	key_repeat_signal_(
		_event
	);
}
