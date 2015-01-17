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


#ifndef SGE_DINPUT_DEVICE_ADD_ELEMENT_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_ADD_ELEMENT_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace dinput
{
namespace device
{

template<
	typename Map,
	typename Vector,
	typename Function
>
void
add_element(
	DIDEVICEOBJECTINSTANCE const &_data,
	Map &_map,
	Vector &_vector,
	Function _function // nonconst because of VC++12
)
{
	FCPPT_ASSERT_ERROR(
		_map.insert(
			std::make_pair(
				_data.dwOfs,
				fcppt::strong_typedef_construct_cast<
					typename Map::mapped_type
				>(
					_vector.size()
				)
			)
		).second
	);

	_vector.push_back(
		_function(
			_data
		)
	);
}

}
}
}

#endif
