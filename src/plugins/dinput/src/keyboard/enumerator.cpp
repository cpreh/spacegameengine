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


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/keyboard/enumerator.hpp>
#include <sge/dinput/keyboard/key_map.hpp>
#include <sge/dinput/keyboard/translate_key_code.hpp>


sge::dinput::keyboard::enumerator::enumerator()
:
	sge::dinput::device::enumerator(),
	key_map_()
{
}

sge::dinput::keyboard::enumerator::~enumerator()
{
}

sge::dinput::keyboard::key_map const &
sge::dinput::keyboard::enumerator::key_map() const
{
	return
		key_map_;
}

void
sge::dinput::keyboard::enumerator::dispatch(
	DIDEVICEOBJECTINSTANCE const &_data
)
{
	if(
		_data.guidType != GUID_Key
	)
		return;

	key_map_[
		_data.dwOfs
	] =
		sge::dinput::keyboard::translate_key_code(
			_data.dwOfs
		);
}
