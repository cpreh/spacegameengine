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
#include <sge/dinput/dinput_unique_ptr.hpp>
#include <sge/dinput/has_focus.hpp>
#include <sge/dinput/device/object_fwd.hpp>
#include <sge/dinput/joypad/device_fwd.hpp>
#include <sge/dinput/keyboard/device_fwd.hpp>
#include <sge/dinput/mouse/device_fwd.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/windows/system/event/handle_unique_ptr.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/event/base_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/function_fwd.hpp>
#include <fcppt/shared_ptr_decl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
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

	template<
		typename State
	>
	using
	fold_device_function
	=
	fcppt::function<
		State (
			sge::dinput::device::object &,
			State &&
		)
	>;

	typedef
	fcppt::function<
		void (
			sge::dinput::device::object &
		)
	>
	for_each_device_function;
		
	template<
		typename State
	>
	State
	fold_devices(
		State &&,
		fold_device_function<
			State
		> const &
	);

	void
	for_each_device(
		for_each_device_function const &
	);

	void
	acquire_all();

	void
	on_focus_in();

	void
	on_focus_out();

	awl::event::container
	on_handle_ready();

	awl::event::container
	on_event(
		awl::event::base const &
	);

	awl::event::container
	on_window_event(
		awl::window::event::base const &
	);

	static
	BOOL
	CALLBACK
	enum_devices_callback(
		LPCDIDEVICEINSTANCE,
		LPVOID
	);

	fcppt::log::object &log_;

	sge::window::object &window_;

	sge::dinput::dinput_unique_ptr const dinput_;

	awl::backends::windows::window::object &windows_window_;

	awl::backends::windows::system::event::handle_unique_ptr const event_handle_;

	sge::dinput::has_focus has_focus_;

	template<
		typename Type
	>
	using
	device_pointer
	=
	fcppt::shared_ptr<
		Type
	>;

	typedef
	fcppt::shared_ptr<
		sge::dinput::keyboard::device
	>
	keyboard_shared_ptr;

	typedef
	fcppt::shared_ptr<
		sge::dinput::mouse::device
	>
	mouse_shared_ptr;

	typedef
	fcppt::shared_ptr<
		sge::dinput::joypad::device
	>
	joypad_shared_ptr;

	template<
		typename Type
	>
	using
	device_container
	=
	std::vector<
		device_pointer<
			Type
		>
	>;

	device_container<
		sge::dinput::keyboard::device
	>
	keyboards_;

	device_container<
		sge::dinput::mouse::device
	>
	mice_;

	device_container<
		sge::dinput::joypad::device
	>
	joypads_;

	fcppt::signal::auto_connection const event_connection_;

	fcppt::signal::auto_connection const window_event_connection_;
};

}
}

#endif
