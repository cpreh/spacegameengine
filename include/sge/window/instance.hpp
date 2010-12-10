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


#ifndef SGE_WINDOW_INSTANCE_HPP_INCLUDED
#define SGE_WINDOW_INSTANCE_HPP_INCLUDED

#include <sge/window/dim_type.hpp>
#include <sge/symbol.hpp>
#include <awl/window/instance_ptr.hpp>
#include <awl/window/event/processor_ptr.hpp>
#include <awl/system/object_ptr.hpp>
#include <awl/system/event/processor_ptr.hpp>
#include <awl/mainloop/io_service_ptr.hpp>
#include <awl/mainloop/dispatcher_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace window
{

class instance
{
	FCPPT_NONCOPYABLE(
		instance
	)
public:
	SGE_SYMBOL
	explicit
	instance(
		awl::system::object_ptr,
		awl::window::instance_ptr,
		awl::window::event::processor_ptr,
		awl::system::event::processor_ptr,
		awl::mainloop::io_service_ptr
	);

	SGE_SYMBOL
	~instance();

	typedef window::dim_type dim_type;

	SGE_SYMBOL
	dim_type const
	size() const;

	SGE_SYMBOL
	void
	show();

	SGE_SYMBOL
	void
	dispatch();

	SGE_SYMBOL
	awl::system::object_ptr const
	awl_system() const;

	SGE_SYMBOL
	awl::window::instance_ptr const
	awl_instance() const;

	SGE_SYMBOL
	awl::window::event::processor_ptr const
	awl_window_event_processor() const;

	SGE_SYMBOL
	awl::system::event::processor_ptr const
	awl_system_event_processor() const;

	SGE_SYMBOL
	awl::mainloop::io_service_ptr const
	awl_io_service() const;
private:
	awl::system::object_ptr const system_;

	awl::window::instance_ptr const instance_;

	awl::window::event::processor_ptr const window_processor_;

	awl::system::event::processor_ptr const system_processor_;

	awl::mainloop::io_service_ptr const io_service_;

	awl::mainloop::dispatcher_ptr const dispatcher_;
};

}
}

#endif
