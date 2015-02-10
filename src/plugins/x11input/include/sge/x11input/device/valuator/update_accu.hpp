/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_UPDATE_ACCU_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_UPDATE_ACCU_HPP_INCLUDED

#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace valuator
{

template<
	typename Result
>
std::pair<
	Result,
	sge::x11input::device::valuator::accu
>
update_accu(
	sge::x11input::device::valuator::accu _accu,
	sge::x11input::device::valuator::value const _value
)
{
	_accu +=
		sge::x11input::device::valuator::accu{
			_value.get()
		};

	Result const diff{
		fcppt::cast::float_to_int<
			Result
		>(
			_accu.get()
		)
	};

	_accu -=
		sge::x11input::device::valuator::accu{
			fcppt::cast::int_to_float<
				sge::x11input::device::valuator::accu::value_type
			>(
				diff
			)
		};

	return
		std::make_pair(
			diff,
			_accu
		);
}

}
}
}
}

#endif
