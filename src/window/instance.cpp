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


#include <sge/window/instance.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <awl/event/processor.hpp>
#include <awl/event/create_processor.hpp>
#include <awl/window/instance.hpp>

sge::window::instance::instance(
	awl::window::instance_ptr const _instance
)
:
	instance_(
		_instance
	),
	processor_(
		awl::event::create_processor(
			_instance
		)
	)
{}

sge::window::instance::~instance()
{}

sge::window::dim_type const
sge::window::instance::size() const
{
	return window::dim_type::null(); // FIXME
}

void
sge::window::instance::show()
{
	instance_->show();
}

sge::mainloop::io_service_ptr const
sge::window::instance::io_service() const
{
	return mainloop::io_service_ptr(); // TODO!
}

void
sge::window::instance::dispatch()
{
	processor_->dispatch();
}

awl::window::instance_ptr const
sge::window::instance::awl_instance() const
{
	return instance_;
}

awl::event::processor_ptr const
sge::window::instance::awl_event_processor() const
{
	return processor_;
}
