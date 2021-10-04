//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_OBJECT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_OBJECT_HPP_INCLUDED

#include <sge/evdev/device/event_fwd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/device/object.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/object_fwd.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/posix/processor_ref.hpp>
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::evdev::joypad
{

class object // NOLINT(fuchsia-multiple-inheritance)
:
	public
		sge::input::joypad::device,
	public
		sge::evdev::device::object,
	public
		fcppt::enable_shared_from_this<
			sge::evdev::joypad::object
		>
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		sge::evdev::device::fd_unique_ptr &&,
		std::filesystem::path &&,
		sge::window::object_ref,
		awl::backends::posix::processor_ref,
		sge::evdev::joypad::info &&
	);

	~object()
	override;
private:
	sge::window::object &
	window() const
	override;

	sge::input::joypad::info const &
	info() const
	override;

	awl::event::optional_base_unique_ptr
	process_event(
		sge::evdev::device::event const &
	)
	override;

	sge::input::joypad::ff::effect_unique_ptr
	create_ff_effect(
		sge::input::joypad::ff::parameters const &
	)
	override;

	sge::window::object_ref const window_;

	sge::evdev::joypad::info const info_;
};

}

#endif
