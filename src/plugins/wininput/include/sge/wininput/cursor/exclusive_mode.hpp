/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_WININPUT_CURSOR_EXCLUSIVE_MODE_HPP_INCLUDED
#define SGE_WININPUT_CURSOR_EXCLUSIVE_MODE_HPP_INCLUDED

#include <sge/wininput/cursor/exclusive_mode_fwd.hpp>
#include <awl/backends/windows/event/type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/signal/auto_connection_container.hpp>


namespace sge
{
namespace wininput
{
namespace cursor
{

class exclusive_mode
{
	FCPPT_NONCOPYABLE(
		exclusive_mode
	);
public:
	exclusive_mode(
		awl::backends::windows::window::event::processor &,
		awl::backends::windows::window::object &
	);

	~exclusive_mode();
private:
	awl::backends::windows::window::event::return_type
	on_temp_unacquire(
		awl::backends::windows::event::type,
		awl::backends::windows::window::event::object const &
	);

	awl::backends::windows::window::event::return_type
	on_temp_acquire(
		awl::backends::windows::event::type,
		awl::backends::windows::window::event::object const &
	);

	fcppt::signal::auto_connection_container
	make_connection_pair(
		awl::backends::windows::window::event::processor &,
		awl::backends::windows::event::type::value_type enter_event,
		awl::backends::windows::event::type::value_type exit_event
	);

	typedef
	fcppt::optional::object<
		awl::backends::windows::event::type
	>
	optional_event_type;

	optional_event_type grab_event_;

	awl::backends::windows::window::object &window_;

	fcppt::signal::auto_connection_container const connections_;
};

}
}
}

#endif
