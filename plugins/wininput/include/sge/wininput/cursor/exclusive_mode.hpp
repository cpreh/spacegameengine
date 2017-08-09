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


#ifndef SGE_WININPUT_CURSOR_EXCLUSIVE_MODE_HPP_INCLUDED
#define SGE_WININPUT_CURSOR_EXCLUSIVE_MODE_HPP_INCLUDED

#include <sge/window/object_fwd.hpp>
#include <sge/wininput/cursor/exclusive_mode_fwd.hpp>
#include <awl/backends/windows/message_type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/generic_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>


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
		sge::window::object &,
		awl::backends::windows::window::object &
	);

	~exclusive_mode();
private:
	awl::event::container
	on_event(
		awl::window::event::base const &
	);

	void
	on_window_event(
		awl::backends::windows::window::event::generic const &
	);

	void
	on_temp_unacquire(
		awl::backends::windows::message_type
	);

	void
	on_temp_acquire(
		awl::backends::windows::message_type
	);

	typedef
	fcppt::optional::object<
		awl::backends::windows::message_type
	>
	optional_event_type;

	optional_event_type grab_event_;

	awl::backends::windows::window::object &window_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif
