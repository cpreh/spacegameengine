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


#ifndef SGE_DINPUT_DEVICE_PARAMETERS_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_PARAMETERS_HPP_INCLUDED

#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/dinput/di.hpp>
#include <awl/backends/windows/system/event/handle_fwd.hpp>
#include <awl/backends/windows/window/instance_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace dinput
{
namespace device
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		IDirectInput8 *,
		fcppt::string const &name,
		GUID,
		awl::backends::windows::window::instance &,
		awl::backends::windows::system::event::handle &
	);

	IDirectInput8 *
	instance() const;

	fcppt::string const
	name() const;

	GUID
	guid() const;

	awl::backends::windows::window::instance &
	window() const;

	awl::backends::windows::system::event::handle &
	event_handle() const;
private:
	IDirectInput8 *const instance_;

	fcppt::string const name_;

	GUID const guid_;

	awl::backends::windows::window::instance &window_;

	awl::backends::windows::system::event::handle &event_handle_;
};

}
}
}

#endif
