/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11input/mask_is_set.hpp>
#include <sge/x11input/device/foreach_valuator.hpp>
#include <sge/x11input/device/valuator_callback.hpp>
#include <sge/x11input/device/valuator_index.hpp>
#include <sge/x11input/device/valuator_value.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <climits>
#include <fcppt/config/external_end.hpp>


void
sge::x11input::device::foreach_valuator(
	XIValuatorState const &_valuators,
	sge::x11input::device::valuator_callback const &_callback
)
{
	if(
		_valuators.mask_len == 0
	)
		return;

	double const *valuator(
		_valuators.values
	);

	for(
		int index = 0;
		index < _valuators.mask_len * CHAR_BIT;
		++index
	)
	{
		if(
			sge::x11input::mask_is_set(
				_valuators.mask,
				index
			)
		)
		{
			_callback(
				fcppt::strong_typedef_construct_cast<
					sge::x11input::device::valuator_index
				>(
					index
				),
				sge::x11input::device::valuator_value(
					*valuator
				)
			);

			++valuator;
		}
	}
}
