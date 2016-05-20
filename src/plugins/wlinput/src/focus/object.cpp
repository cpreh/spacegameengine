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


#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


sge::wlinput::focus::object::object(
	awl::backends::wayland::seat const &_seat
)
:
	sge::input::focus::object(),
	char_signal_{},
	key_signal_{},
	key_repeat_signal_{},
	in_signal_{},
	out_signal_{}
{
}

sge::wlinput::focus::object::~object()
{
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::char_callback(
	sge::input::focus::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::key_callback(
	sge::input::focus::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::key_repeat_callback(
	sge::input::focus::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::in_callback(
	sge::input::focus::in_callback const &_callback
)
{
	return
		in_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::wlinput::focus::object::out_callback(
	sge::input::focus::out_callback const &_callback
)
{
	return
		out_signal_.connect(
			_callback
		);
}
