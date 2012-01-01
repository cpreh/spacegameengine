/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/window/object_ptr.hpp>
#include <sge/window/system.hpp>
#include <awl/event/processor.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/system/event/processor_fwd.hpp>
#include <awl/window/instance_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>


sge::window::system::system(
	awl::system::object &_awl_system,
	awl::system::event::processor &_awl_system_event_processor,
	awl::event::processor &_awl_event_processor
)
:
	awl_system_(
		_awl_system
	),
	awl_system_event_processor_(
		_awl_system_event_processor
	),
	awl_event_processor_(
		_awl_event_processor
	)
{
}

sge::window::system::~system()
{
}

awl::system::object &
sge::window::system::awl_system() const
{
	return awl_system_;
}

awl::event::processor &
sge::window::system::awl_event_processor() const
{
	return awl_event_processor_;
}

awl::system::event::processor &
sge::window::system::awl_system_event_processor() const
{
	return awl_system_event_processor_;
}

sge::window::object_ptr const
sge::window::system::create(
	awl::window::instance &_awl_window,
	awl::window::event::processor &_awl_window_event_processor
) const
{
	return
		fcppt::make_shared_ptr<
			sge::window::object
		>(
			fcppt::ref(
				_awl_window
			),
			fcppt::ref(
				_awl_window_event_processor
			),
			fcppt::ref(
				awl_event_processor_
			)
		);
}

bool
sge::window::system::poll()
{
	return
		awl_event_processor_.poll();
}

void
sge::window::system::next()
{
	awl_event_processor_.next();
}
