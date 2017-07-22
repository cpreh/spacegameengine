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


#include <sge/window/poll.hpp>
#include <sge/window/poll_function.hpp>
#include <sge/window/system.hpp>
#include <awl/main/exit_code.hpp>


awl::main::exit_code
sge::window::poll(
	sge::window::system &_system,
	sge::window::poll_function const &_function
)
{
	while(
		_system.poll()
	)
		_function();

	return
		_system.exit_code();
}
