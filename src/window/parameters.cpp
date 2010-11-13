/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
	awl::window::instance_ptr const _window
)
:
	window_(_window)
{
}

sge::window::parameters &
sge::window::parameters::event_processor(
	awl::event::processor_ptr const _event_processor
)
{
	event_processor_ = _event_processor;

	return *this;
}

sge::window::parameters &
sge::window::parameters::io_service(
	awl::mainloop::io_service_ptr const _io_service
)
{
	io_service_ = _io_service;

	return *this;
}

awl::window::instance_ptr const
sge::window::parameters::window() const
{
	return window_;
}

awl::event::processor_ptr const
sge::window::parameters::event_processor() const
{
	return event_processor_;
}

awl::mainloop::io_service_ptr const
sge::window::parameters::io_service() const
{
	return io_service_;
}
