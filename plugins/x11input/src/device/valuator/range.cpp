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


#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/iterator.hpp>
#include <sge/x11input/device/valuator/length.hpp>
#include <sge/x11input/device/valuator/range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::device::valuator::range::range(
	XIValuatorState const &_state
)
:
	state_{
		_state
	}
{
}

sge::x11input::device::valuator::range::iterator
sge::x11input::device::valuator::range::begin() const
{
	return
		sge::x11input::device::valuator::range::iterator{
			sge::x11input::device::valuator::index{
				0
			},
			state_.get()
		};
}

sge::x11input::device::valuator::range::iterator
sge::x11input::device::valuator::range::end() const
{
	return
		sge::x11input::device::valuator::range::iterator{
			sge::x11input::device::valuator::length(
				state_.get()
			),
			state_.get()
		};
}
