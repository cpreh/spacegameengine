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
#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/char_event_fwd.hpp>
#include <sge/input/focus/collector.hpp>
#include <sge/input/focus/count.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/discover_event_fwd.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_event_fwd.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event_fwd.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/key_repeat_event_fwd.hpp>
#include <sge/input/focus/manager.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/input/focus/out_event_fwd.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/focus/remove_event_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


sge::input::focus::collector::collector(
	sge::input::processor &_processor
)
:
	in_count_(
		0u
	),
	char_signal_(),
	key_signal_(),
	key_repeat_signal_(),
	in_signal_(),
	out_signal_(),
	manager_(
		_processor,
		sge::input::focus::discover_callback{
			[](
				sge::input::focus::discover_event const &
			){}
		},
		sge::input::focus::remove_callback{
			[](
				sge::input::focus::remove_event const &
			){}
		},
		sge::input::focus::manager::char_callback{
			[
				this
			](
				sge::input::focus::object &,
				sge::input::focus::char_event const &_event
			)
			{
				char_signal_(
					_event
				);
			}
		},
		sge::input::focus::manager::key_callback{
			[
				this
			](
				sge::input::focus::object &,
				sge::input::focus::key_event const &_event
			)
			{
				key_signal_(
					_event
				);
			}
		},
		sge::input::focus::manager::key_repeat_callback{
			[
				this
			](
				sge::input::focus::object &,
				sge::input::focus::key_repeat_event const &_event
			)
			{
				key_repeat_signal_(
					_event
				);
			}
		},
		sge::input::focus::manager::in_callback{
			[
				this
			](
				sge::input::focus::object &,
				sge::input::focus::in_event const &_event
			)
			{
				if(
					++in_count_
					==
					sge::input::focus::count{
						1u
					}
				)
					in_signal_(
						_event
					);
			}
		},
		sge::input::focus::manager::out_callback{
			[
				this
			](
				sge::input::focus::object &,
				sge::input::focus::out_event const &_event
			)
			{
				if(
					in_count_
					!=
					sge::input::focus::count{
						0u
					}
				)
					--in_count_;

				if(
					in_count_
					==
					sge::input::focus::count{
						0u
					}
				)
					out_signal_(
						_event
					);
			}
		}
	)
{
}

sge::input::focus::collector::~collector()
{
}

fcppt::signal::auto_connection
sge::input::focus::collector::char_callback(
	sge::input::focus::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::focus::collector::key_callback(
	sge::input::focus::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::focus::collector::key_repeat_callback(
	sge::input::focus::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::focus::collector::in_callback(
	sge::input::focus::in_callback const &_callback
)
{
	return
		in_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::focus::collector::out_callback(
	sge::input::focus::out_callback const &_callback
)
{
	return
		out_signal_.connect(
			_callback
		);
}
