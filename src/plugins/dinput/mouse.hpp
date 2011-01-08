/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_DINPUT_MOUSE_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_HPP_INCLUDED

#include "device.hpp"
#include "device_parameters_fwd.hpp"
#include "di.hpp"
#include <sge/input/mouse/device.hpp>
#include <fcppt/noncopyable.hpp>
#include <map>

namespace sge
{
namespace dinput
{

class mouse
:
	public sge::input::mouse::device,
	public dinput::device
{
	FCPPT_NONCOPYABLE(
		mouse
	)
public:
	explicit mouse(
		dinput::device_parameters const &
	);

	~mouse();

	fcppt::signal::auto_connection
	button_callback(
		mouse::button_callback const &
	);

	fcppt::signal::auto_connection
	axis_callback(
		mouse::axis_callback const &
	);

	void
	dispatch();
private:
	static BOOL CALLBACK
	enum_mouse_keys(
		LPCDIDEVICEOBJECTINSTANCE,
		LPVOID
	);

	typedef fcppt::signal::object<
		sge::input::mouse::button_function
	> button_signal;

	typedef fcppt::signal::object<
		sge::input::mouse::axis_function
	> axis_signal;

	button_signal button_signal_;

	axis_signal axis_signal_;

	typedef std::map<
		UINT,
		input::key_type
	> key_map;

	key_map keys_;
};

}
}

#endif
