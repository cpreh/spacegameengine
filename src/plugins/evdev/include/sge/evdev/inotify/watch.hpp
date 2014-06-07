/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_EVDEV_INOTIFY_WATCH_HPP_INCLUDED
#define SGE_EVDEV_INOTIFY_WATCH_HPP_INCLUDED

#include <sge/evdev/inotify/object_fwd.hpp>
#include <sge/evdev/inotify/watch_fwd.hpp>
#include <awl/backends/linux/fd/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace inotify
{

class watch
{
	FCPPT_NONCOPYABLE(
		watch
	);
public:
	watch(
		boost::filesystem::path const &,
		sge::evdev::inotify::object const &
	);

	~watch();
private:
	sge::evdev::inotify::object const &object_;

	awl::backends::linux::fd::object const fd_;
};

}
}
}

#endif
