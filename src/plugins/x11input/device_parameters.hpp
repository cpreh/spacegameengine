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


#ifndef SGE_X11INPUT_DEVICE_PARAMETERS_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_PARAMETERS_HPP_INCLUDED

#include "device_parameters_fwd.hpp"
#include <awl/backends/x11/system/event/opcode.hpp>
#include <awl/backends/x11/system/event/processor_ptr.hpp>
#include <awl/backends/x11/window/instance_ptr.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace x11input
{

class device_parameters
{
	FCPPT_NONASSIGNABLE(
		device_parameters
	)
public:
	device_parameters(
		int id,
		awl::backends::x11::system::event::opcode,
		awl::backends::x11::window::instance_ptr,
		awl::backends::x11::system::event::processor_ptr
	);

	int
	id() const;

	awl::backends::x11::system::event::opcode const
	opcode() const;

	awl::backends::x11::window::instance_ptr const
	window() const;

	awl::backends::x11::system::event::processor_ptr const
	processor() const;
private:
	int const id_;

	awl::backends::x11::system::event::opcode const opcode_;

	awl::backends::x11::window::instance_ptr const window_;

	awl::backends::x11::system::event::processor_ptr const processor_;
};

}
}

#endif
