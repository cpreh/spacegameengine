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


#ifndef SGE_EVDEV_INOTIFY_READER_HPP_INCLUDED
#define SGE_EVDEV_INOTIFY_READER_HPP_INCLUDED

#include <sge/evdev/inotify/callback.hpp>
#include <sge/evdev/inotify/object.hpp>
#include <sge/evdev/inotify/reader_fwd.hpp>
#include <sge/evdev/inotify/watch.hpp>
#include <awl/backends/linux/fd/event_fwd.hpp>
#include <awl/backends/linux/fd/processor_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace inotify
{

class reader
{
	FCPPT_NONCOPYABLE(
		reader
	);
public:
	reader(
		boost::filesystem::path const &,
		awl::backends::linux::fd::processor &,
		sge::evdev::inotify::callback const &
	);

	~reader();
private:
	void
	on_read(
		awl::backends::linux::fd::event const &
	);

	sge::evdev::inotify::object const object_;

	sge::evdev::inotify::watch const watch_;

	fcppt::signal::auto_connection const fd_connection_;

	sge::evdev::inotify::callback const callback_;
};

}
}
}

#endif
