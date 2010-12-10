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


#ifndef SGE_WINDOW_PARAMETERS_HPP_INCLUDED
#define SGE_WINDOW_PARAMETERS_HPP_INCLUDED

#include <sge/window/parameters_fwd.hpp>
#include <sge/symbol.hpp>
#include <awl/window/instance_ptr.hpp>
#include <awl/window/event/processor_ptr.hpp>
#include <awl/system/object_ptr.hpp>
#include <awl/system/event/processor_ptr.hpp>
#include <awl/mainloop/io_service_ptr.hpp>

namespace sge
{
namespace window
{

class parameters
{
public:
	SGE_SYMBOL
	parameters(
		awl::system::object_ptr,
		awl::window::instance_ptr
	);

	SGE_SYMBOL
	parameters &
	window_event_processor(
		awl::window::event::processor_ptr
	);

	SGE_SYMBOL
	parameters &
	system_event_processor(
		awl::system::event::processor_ptr
	);

	SGE_SYMBOL
	parameters &
	io_service(
		awl::mainloop::io_service_ptr
	);

	SGE_SYMBOL
	awl::system::object_ptr const
	system() const;

	SGE_SYMBOL
	awl::window::instance_ptr const
	window() const;

	SGE_SYMBOL
	awl::window::event::processor_ptr const
	window_event_processor() const;

	SGE_SYMBOL
	awl::system::event::processor_ptr const
	system_event_processor() const;

	SGE_SYMBOL
	awl::mainloop::io_service_ptr const
	io_service() const;
private:
	awl::system::object_ptr system_;

	awl::window::instance_ptr window_;

	awl::window::event::processor_ptr window_event_processor_;

	awl::system::event::processor_ptr system_event_processor_;

	awl::mainloop::io_service_ptr io_service_;
};

}
}

#endif
