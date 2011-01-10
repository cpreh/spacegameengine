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


#include "../parameters.hpp"

sge::x11input::device::parameters::parameters(
	x11input::device::id const &_id,
	awl::backends::x11::system::event::opcode const _opcode,
	awl::backends::x11::window::instance_ptr const _window,
	x11input::device::window_demuxer &_window_demuxer,
	x11input::device::raw_demuxer &_raw_demuxer
)
:
	id_(_id),
	opcode_(_opcode),
	window_(_window),
	window_demuxer_(_window_demuxer),
	raw_demuxer_(_raw_demuxer)
{
}

sge::x11input::device::id const
sge::x11input::device::parameters::id() const
{
	return id_;
}

awl::backends::x11::system::event::opcode const
sge::x11input::device::parameters::opcode() const
{
	return opcode_;
}

awl::backends::x11::window::instance_ptr const
sge::x11input::device::parameters::window() const
{
	return window_;
}

sge::x11input::device::window_demuxer &
sge::x11input::device::parameters::window_demuxer() const
{
	return window_demuxer_;
}

sge::x11input::device::raw_demuxer &
sge::x11input::device::parameters::raw_demuxer() const
{
	return raw_demuxer_;
}
