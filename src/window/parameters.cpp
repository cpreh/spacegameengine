/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/window/parameters.hpp>

sge::window::parameters::parameters(
	awl::system::object_shared_ptr const _system,
	awl::window::instance_shared_ptr const _window
)
:
	system_(_system),
	window_(_window),
	window_event_processor_(),
	system_event_processor_(),
	io_service_()
{
}

sge::window::parameters &
sge::window::parameters::window_event_processor(
	awl::window::event::processor_shared_ptr const _window_event_processor
)
{
	window_event_processor_ = _window_event_processor;

	return *this;
}

sge::window::parameters &
sge::window::parameters::system_event_processor(
	awl::system::event::processor_shared_ptr const _system_event_processor
)
{
	system_event_processor_ = _system_event_processor;

	return *this;
}

sge::window::parameters &
sge::window::parameters::io_service(
	awl::mainloop::io_service_shared_ptr const _io_service
)
{
	io_service_ = _io_service;

	return *this;
}

awl::system::object_shared_ptr const
sge::window::parameters::system() const
{
	return system_;
}

awl::window::instance_shared_ptr const
sge::window::parameters::window() const
{
	return window_;
}

awl::window::event::processor_shared_ptr const
sge::window::parameters::window_event_processor() const
{
	return window_event_processor_;
}

awl::system::event::processor_shared_ptr const
sge::window::parameters::system_event_processor() const
{
	return system_event_processor_;
}

awl::mainloop::io_service_shared_ptr const
sge::window::parameters::io_service() const
{
	return io_service_;
}
