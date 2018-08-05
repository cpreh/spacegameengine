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


#include <sge/input/key/code.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/systems/detail/quit_on_escape.hpp>
#include <sge/window/system.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sge::systems::detail::quit_on_escape(
	sge::window::system &_window_system,
	awl::event::base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic<
			sge::input::keyboard::event::key const
		>(
			_event
		),
		[
			&_window_system
		](
			fcppt::reference<
				sge::input::keyboard::event::key const
			> const _key_event
		)
		{
			if(
				!_key_event.get().pressed()
				&&
				_key_event.get().get().code()
				==
				sge::input::key::code::escape
			)
				_window_system.quit(
					awl::main::exit_success()
				);
		}
	);
}
