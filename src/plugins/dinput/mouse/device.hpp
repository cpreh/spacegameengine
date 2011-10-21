/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_DINPUT_MOUSE_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_DEVICE_HPP_INCLUDED

#include "device_fwd.hpp"
#include "../device/object.hpp"
#include "../device/parameters_fwd.hpp"
#include "../di.hpp"
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/axis_signal.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_signal.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace dinput
{
namespace mouse
{

class device
:
	public sge::input::mouse::device,
	public dinput::device::object
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	explicit device(
		dinput::device::parameters const &
	);

	~device();

	fcppt::signal::auto_connection
	axis_callback(
		input::mouse::axis_callback const &
	);

	fcppt::signal::auto_connection
	button_callback(
		input::mouse::button_callback const &
	);

	sge::input::mouse::info const &
	info() const;

	void
	dispatch();
private:
	static BOOL CALLBACK
	enum_mouse_keys(
		LPCDIDEVICEOBJECTINSTANCE,
		LPVOID
	);

	sge::input::mouse::info info_;

	sge::input::mouse::axis_signal axis_signal_;

	sge::input::mouse::button_signal button_signal_;

	typedef std::map<
		DWORD,
		input::mouse::axis_code::type
	> axis_map;

	typedef std::map<
		DWORD,
		input::mouse::button_code::type
	> button_map;

	axis_map axis_;

	button_map buttons_;
};

}
}
}

#endif
