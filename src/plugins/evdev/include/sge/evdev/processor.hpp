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


#ifndef SGE_EVDEV_PROCESSOR_HPP_INCLUDED
#define SGE_EVDEV_PROCESSOR_HPP_INCLUDED

#include <sge/evdev/focus_manager.hpp>
#include <sge/evdev/eventfd/object_fwd.hpp>
#include <sge/evdev/inotify/event_fwd.hpp>
#include <sge/evdev/inotify/reader_fwd.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_signal.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_signal.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/backends/linux/fd/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/optional_auto_connection_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
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
		sge::window::object const &,
		sge::window::system const &
	);

	~processor()
	override;
private:
	fcppt::signal::optional_auto_connection
	keyboard_discover_callback(
		sge::input::keyboard::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	keyboard_remove_callback(
		sge::input::keyboard::remove_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	mouse_discover_callback(
		sge::input::mouse::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	mouse_remove_callback(
		sge::input::mouse::remove_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	focus_discover_callback(
		sge::input::focus::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	focus_remove_callback(
		sge::input::focus::remove_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	cursor_discover_callback(
		sge::input::cursor::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	cursor_remove_callback(
		sge::input::cursor::remove_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	joypad_discover_callback(
		sge::input::joypad::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	joypad_remove_callback(
		sge::input::joypad::remove_callback const &
	)
	override;

	void
	dev_init();

	void
	dev_event(
		sge::evdev::inotify::event const &
	);

	sge::input::joypad::discover_signal joypad_discover_;

	sge::input::joypad::remove_signal joypad_remove_;

	sge::evdev::joypad::map joypads_;

	sge::evdev::focus_manager const focus_manager_;

	boost::filesystem::path const path_;

	awl::backends::linux::fd::processor &processor_;

	typedef
	fcppt::unique_ptr<
		sge::evdev::eventfd::object
	>
	eventfd_unique_ptr;

	eventfd_unique_ptr const eventfd_;

	typedef
	fcppt::unique_ptr<
		sge::evdev::inotify::reader
	>
	inotify_reader_unique_ptr;

	typedef
	fcppt::optional::object<
		inotify_reader_unique_ptr
	>
	optional_inotify_reader_unique_ptr;

	optional_inotify_reader_unique_ptr dev_reader_;
};

}
}

#endif
