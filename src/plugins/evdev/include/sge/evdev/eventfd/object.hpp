/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_EVDEV_EVENTFD_OBJECT_HPP_INCLUDED
#define SGE_EVDEV_EVENTFD_OBJECT_HPP_INCLUDED

#include <sge/evdev/eventfd/callback.hpp>
#include <sge/evdev/eventfd/fd.hpp>
#include <sge/evdev/eventfd/object_fwd.hpp>
#include <awl/backends/linux/fd/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace evdev
{
namespace eventfd
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		awl::backends::linux::fd::processor &,
		sge::evdev::eventfd::callback const &
	);

	~object();

	void
	write();

	void
	read();
private:
	sge::evdev::eventfd::fd const fd_;

	fcppt::signal::scoped_connection const fd_connection_;
};

}
}
}

#endif
