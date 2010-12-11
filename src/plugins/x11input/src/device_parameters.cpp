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


#include "../device_parameters.hpp"

sge::x11input::device_parameters::device_parameters(
	int const _id,
	awl::backends::x11::system::event::opcode const _opcode,
	awl::backends::x11::window::instance_ptr const _window,
	awl::backends::x11::system::event::processor_ptr const _processor
)
:
	id_(_id),
	opcode_(_opcode),
	window_(_window),
	processor_(_processor)
{
}

int
sge::x11input::device_parameters::id() const
{
	return id_;
}

awl::backends::x11::system::event::opcode const
sge::x11input::device_parameters::opcode() const
{
	return opcode_;
}

awl::backends::x11::window::instance_ptr const
sge::x11input::device_parameters::window() const
{
	return window_;
}

awl::backends::x11::system::event::processor_ptr const
sge::x11input::device_parameters::processor() const
{
	return processor_;
}
