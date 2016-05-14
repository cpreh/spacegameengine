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


#include <sge/window/object.hpp>
#include <sge/window/object_unique_ptr.hpp>
#include <sge/window/system.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/processor.hpp>
#include <awl/window/object_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::window::system::system(
	awl::system::object &_awl_system
)
:
	awl_system_(
		_awl_system
	),
	exit_code_()
{
}

sge::window::system::~system()
{
}

awl::system::object &
sge::window::system::awl_system() const
{
	return
		awl_system_;
}

awl::system::event::processor &
sge::window::system::awl_system_event_processor() const
{
	return
		awl_system_.processor();
}

sge::window::object_unique_ptr
sge::window::system::create(
	awl::window::object &_awl_window
) const
{
	return
		fcppt::make_unique_ptr<
			sge::window::object
		>(
			_awl_window
		);
}

bool
sge::window::system::poll()
{
	exit_code_ =
		this->awl_system_event_processor().poll();

	return
		this->running();
}

bool
sge::window::system::next()
{
	exit_code_ =
		this->awl_system_event_processor().next();

	return
		this->running();
}

bool
sge::window::system::running() const
{
	return
		!exit_code_.has_value();
}

void
sge::window::system::quit(
	awl::main::exit_code const _exit_code
)
{
	this->awl_system_event_processor().quit(
		_exit_code
	);
}

awl::main::exit_code
sge::window::system::exit_code() const
{
	// FIXME
	return
		exit_code_.get_unsafe();
}
