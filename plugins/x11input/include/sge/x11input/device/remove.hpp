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


#ifndef SGE_X11INPUT_DEVICE_REMOVE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_REMOVE_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/map.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/find_opt_iterator.hpp>


namespace sge
{
namespace x11input
{
namespace device
{

template<
	typename Type
>
fcppt::shared_ptr<
	Type
>
remove(
	sge::x11input::device::map<
		Type
	> &_map,
	sge::x11input::device::id const _id
)
{
	typedef
	typename
	sge::x11input::device::map<
		Type
	>::iterator
	iterator_type;

	iterator_type const iterator{
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::find_opt_iterator(
				_map,
				_id
			)
		)
	};

	fcppt::shared_ptr<
		Type
	>
	result{
		iterator->second
	};

	_map.erase(
		iterator
	);

	return
		result;
}

}
}
}

#endif
