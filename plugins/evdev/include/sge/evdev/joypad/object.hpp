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
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{

class object
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
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::evdev::device::fd_unique_ptr &&,
		boost::filesystem::path const &,
		sge::window::object &,
		sge::evdev::joypad::info const &
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

	sge::window::object &window_;

	sge::evdev::joypad::info const info_;
};

}
}
}

#endif
