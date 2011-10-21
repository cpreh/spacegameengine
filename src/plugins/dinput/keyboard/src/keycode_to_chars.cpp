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


#include "../keycode_to_chars.hpp"
#include "../../di.hpp"
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>


sge::dinput::keyboard::char_vector const
sge::dinput::keyboard::keycode_to_chars(
	UINT const _virtual_code,
	UINT const _di_code,
	dinput::state_array const &_states,
	HKL const _kblayout
)
{
	// FIXME: How do we determine how big this buffer should be?
	dinput::keyboard::char_vector result(
		32
	);

	int const ret(
		::ToUnicodeEx(
			_virtual_code,
			_di_code,
			_states.data(),
			result.data(),
			static_cast<
				int
			>(
				result.size()
			),
			0,
			_kblayout
		)
	);

	if(
		ret < -1
	)
		throw sge::input::exception(
			FCPPT_TEXT("Invalid return value of ToUnicodeEx!")
		);

	if(
		ret == -1
	)
		return dinput::keyboard::char_vector();

	result.resize(
		static_cast<
			dinput::keyboard::char_vector::size_type
		>(
			ret
		)
	);

	return result;
}
