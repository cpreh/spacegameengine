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


#include <sge/window/instance.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <awl/system/event/processor.hpp>
#include <awl/window/event/processor.hpp>
#include <awl/window/instance.hpp>
#include <awl/mainloop/io_service.hpp>
#include <awl/mainloop/dispatcher.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::window::instance::instance(
	awl::system::object_shared_ptr const _system,
	awl::window::instance_shared_ptr const _instance,
	awl::window::event::processor_shared_ptr const _window_processor,
	awl::system::event::processor_shared_ptr const _system_processor,
	awl::mainloop::io_service_shared_ptr const _io_service
)
:
	system_(
		_system
	),
	instance_(
		_instance
	),
	window_processor_(
		_window_processor
	),
	system_processor_(
		_system_processor
	),
	io_service_(
		_io_service
	),
	dispatcher_(
		io_service_
		?
			io_service_->create_dispatcher(
				*system_,
				std::tr1::bind(
					&instance::dispatch,
					this
				)
			)
		:
			awl::mainloop::dispatcher_unique_ptr()
	)
{
}
FCPPT_PP_POP_WARNING

sge::window::instance::~instance()
{
}

sge::window::dim const
sge::window::instance::size() const
{
	return
		fcppt::math::dim::structure_cast<
			sge::window::dim
		>(
			instance_->size()
		);
}

void
sge::window::instance::show()
{
	instance_->show();
}

bool
sge::window::instance::dispatch()
{
	// events might come in any order
	// so make sure to process as much as possible in one go
	bool events_processed = false;

	bool more_messages = true;

	while(
		more_messages
	)
	{
		more_messages =
			system_processor_->dispatch();

		more_messages =
			window_processor_->dispatch()
			||
			more_messages;

		if(
			more_messages
		)
			events_processed = true;
		else
			break;
	}

	return events_processed;
}

awl::system::object_shared_ptr const
sge::window::instance::awl_system() const
{
	return system_;
}

awl::window::instance_shared_ptr const
sge::window::instance::awl_instance() const
{
	return instance_;
}

awl::window::event::processor_shared_ptr const
sge::window::instance::awl_window_event_processor() const
{
	return window_processor_;
}

awl::system::event::processor_shared_ptr const
sge::window::instance::awl_system_event_processor() const
{
	return system_processor_;
}

awl::mainloop::io_service_shared_ptr const
sge::window::instance::awl_io_service() const
{
	return io_service_;
}

awl::mainloop::dispatcher *
sge::window::instance::awl_dispatcher() const
{
	return dispatcher_.get();
}
