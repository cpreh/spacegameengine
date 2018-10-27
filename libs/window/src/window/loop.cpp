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


#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/system.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/system/event/result.hpp>
#include <fcppt/assert/unreachable.hpp>


awl::main::exit_code
sge::window::loop(
	sge::window::system &_system,
	sge::window::loop_function const &_function
)
{
	// TODO: This is ugly
	for(
		;;
	)
	{
		awl::system::event::result const result{
			_system.next()
		};

		if(
			result.has_failure()
		)
			return
				result.get_failure_unsafe();

		for(
			awl::event::base_unique_ptr const &event
			:
			result.get_success_unsafe()
		)
			_function(
				*event
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
