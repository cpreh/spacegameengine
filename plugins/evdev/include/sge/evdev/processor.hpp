//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_PROCESSOR_HPP_INCLUDED
#define SGE_EVDEV_PROCESSOR_HPP_INCLUDED

#include <sge/evdev/inotify/event_fwd.hpp>
#include <sge/evdev/inotify/reader.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/posix/event_fwd.hpp>
#include <awl/backends/posix/processor_fwd.hpp>
#include <awl/event/connection_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{

class processor
:
	public sge::input::processor
{
	FCPPT_NONCOPYABLE(
		processor
	);
public:
	processor(
		fcppt::log::object &,
		sge::window::object &
	);

	~processor()
	override;
private:
	sge::window::object &
	window() const
	override;

	sge::input::cursor::container
	cursors() const
	override;

	sge::input::focus::container
	foci() const
	override;

	sge::input::joypad::container
	joypads() const
	override;

	sge::input::keyboard::container
	keyboards() const
	override;

	sge::input::mouse::container
	mice() const
	override;

	awl::event::container
	system_event(
		awl::event::base const &
	);

	awl::event::container
	fd_event(
		awl::backends::posix::event const &
	);

	awl::event::optional_base_unique_ptr
	inotify_event(
		sge::evdev::inotify::event const &
	);

	awl::event::container
	device_event(
		awl::backends::posix::event const &
	);

	fcppt::log::object &log_;

	std::filesystem::path const path_;

	sge::window::object &window_;

	awl::backends::posix::processor &processor_;

	sge::evdev::inotify::reader dev_watch_;

	awl::event::connection_unique_ptr const dev_watch_connection_;

	sge::evdev::joypad::map joypads_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}

#endif
