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


#ifndef SGE_DINPUT_PROCESSOR_HPP_INCLUDED
#define SGE_DINPUT_PROCESSOR_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/has_focus.hpp>
#include <sge/dinput/device/object_fwd.hpp>
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
#include <sge/input/keyboard/discover_signal.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_signal.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_signal.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_signal.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/backends/windows/system/event/handle_fwd.hpp>
#include <awl/backends/windows/system/event/processor_fwd.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type_fwd.hpp>
#include <awl/backends/windows/window/event/scoped_user_message.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/window/event/focus_in_fwd.hpp>
#include <awl/window/event/focus_out_fwd.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/optional_auto_connection_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace dinput
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
	joypad_discover_callback(
		sge::input::joypad::discover_callback const &
	)
	override;

	fcppt::signal::optional_auto_connection
	joypad_remove_callback(
		sge::input::joypad::remove_callback const &
	)
	override;
private:
	void
	on_focus_in(
		awl::window::event::focus_in const &
	);

	void
	on_focus_out(
		awl::window::event::focus_out const &
	);

	void
	on_handle_ready();

	awl::backends::windows::window::event::return_type
	on_init(
		awl::backends::windows::window::event::object const &
	);

	template<
		typename Function
	>
	void
	for_each_device(
		Function const &
	);

	template<
		typename DiscoverEvent,
		typename Ptr
	>
	void
	add_device(
		fcppt::signal::object<
			void (
				DiscoverEvent const &
			)
		> &,
		Ptr
	);

	static BOOL CALLBACK
	enum_devices_callback(
		LPCDIDEVICEINSTANCE,
		LPVOID
	);

	typedef
	fcppt::unique_ptr<
		sge::dinput::device::object
	>
	device_unique_ptr;

	typedef
	std::vector<
		device_unique_ptr
	>
	device_vector;

	typedef
	fcppt::unique_ptr<
		IDirectInput8,
		fcppt::com_deleter
	>
	dinput_unique_ptr;

	dinput_unique_ptr const dinput_;

	awl::system::object &awl_system_;

	awl::backends::windows::window::object &windows_window_;

	awl::backends::windows::window::event::processor &event_processor_;

	awl::backends::windows::system::event::processor &system_processor_;

	device_vector devices_;

	typedef
	fcppt::unique_ptr<
		awl::backends::windows::system::event::handle
	>
	event_handle_unique_ptr;

	event_handle_unique_ptr const event_handle_;

	sge::dinput::has_focus has_focus_;

	sge::input::keyboard::discover_signal keyboard_discover_;

	sge::input::keyboard::remove_signal keyboard_remove_;

	sge::input::mouse::discover_signal mouse_discover_;

	sge::input::mouse::remove_signal mouse_remove_;

	sge::input::joypad::discover_signal joypad_discover_;

	sge::input::joypad::remove_signal joypad_remove_;

	awl::backends::windows::window::event::scoped_user_message const init_message_;

	fcppt::signal::auto_connection_container const connections_;
};

}
}

#endif
