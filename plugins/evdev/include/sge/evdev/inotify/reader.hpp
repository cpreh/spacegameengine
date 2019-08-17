//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_INOTIFY_READER_HPP_INCLUDED
#define SGE_EVDEV_INOTIFY_READER_HPP_INCLUDED

#include <sge/evdev/inotify/event_container.hpp>
#include <sge/evdev/inotify/object.hpp>
#include <sge/evdev/inotify/reader_fwd.hpp>
#include <sge/evdev/inotify/watch.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
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
	explicit
	reader(
		std::filesystem::path const &
	);

	~reader();

	sge::evdev::inotify::event_container
	on_event();

	awl::backends::posix::fd
	fd() const;
private:
	sge::evdev::inotify::object const object_;

	sge::evdev::inotify::watch const watch_;
};

}
}
}

#endif
