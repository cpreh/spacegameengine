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


#ifndef SGE_WINDOW_INSTANCE_HPP_INCLUDED
#define SGE_WINDOW_INSTANCE_HPP_INCLUDED

#include <sge/window/dim.hpp>
#include <sge/window/symbol.hpp>
#include <awl/window/instance_shared_ptr.hpp>
#include <awl/window/event/processor_shared_ptr.hpp>
#include <awl/system/object_shared_ptr.hpp>
#include <awl/system/event/processor_shared_ptr.hpp>
#include <awl/mainloop/io_service_shared_ptr.hpp>
#include <awl/mainloop/dispatcher_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace window
{

class instance
{
	FCPPT_NONCOPYABLE(
		instance
	);
public:
	SGE_WINDOW_SYMBOL
	explicit
	instance(
		awl::system::object_shared_ptr,
		awl::window::instance_shared_ptr,
		awl::window::event::processor_shared_ptr,
		awl::system::event::processor_shared_ptr,
		awl::mainloop::io_service_shared_ptr
	);

	SGE_WINDOW_SYMBOL
	~instance();

	SGE_WINDOW_SYMBOL
	window::dim const
	size() const;

	SGE_WINDOW_SYMBOL
	void
	show();

	SGE_WINDOW_SYMBOL
	bool
	dispatch();

	SGE_WINDOW_SYMBOL
	awl::system::object_shared_ptr const
	awl_system() const;

	SGE_WINDOW_SYMBOL
	awl::window::instance_shared_ptr const
	awl_instance() const;

	SGE_WINDOW_SYMBOL
	awl::window::event::processor_shared_ptr const
	awl_window_event_processor() const;

	SGE_WINDOW_SYMBOL
	awl::system::event::processor_shared_ptr const
	awl_system_event_processor() const;

	SGE_WINDOW_SYMBOL
	awl::mainloop::io_service_shared_ptr const
	awl_io_service() const;

	SGE_WINDOW_SYMBOL
	awl::mainloop::dispatcher *
	awl_dispatcher() const;
private:
	awl::system::object_shared_ptr const system_;

	awl::window::instance_shared_ptr const instance_;

	awl::window::event::processor_shared_ptr const window_processor_;

	awl::system::event::processor_shared_ptr const system_processor_;

	awl::mainloop::io_service_shared_ptr const io_service_;

	typedef fcppt::scoped_ptr<
		awl::mainloop::dispatcher
	> dispatcher_scoped_ptr;

	dispatcher_scoped_ptr const dispatcher_;
};

}
}

#endif
