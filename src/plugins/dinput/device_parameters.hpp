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

#ifndef SGE_DINPUT_DEVICE_PARAMETERS_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_PARAMETERS_HPP_INCLUDED

#include "device_parameters_fwd.hpp"
#include "di.hpp"
#include "dinput_ptr.hpp"
#include <awl/backends/windows/window/instance_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace dinput
{

class device_parameters
{
	FCPPT_NONASSIGNABLE(
		device_parameters
	)
public:
	device_parameters(
		dinput::dinput_ptr,
		fcppt::string const &name,
		GUID,
		awl::backends::windows::window::instance_ptr
	);
private:
	dinput::dinput_ptr const device_;

	fcppt::string const name_;

	GUID const guid_;

	awl::backends::windows::window::instance_ptr const window_;
};

}
}

#endif
