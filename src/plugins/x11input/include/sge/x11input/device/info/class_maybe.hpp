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


#ifndef SGE_X11INPUT_DEVICE_INFO_CLASS_MAYBE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_CLASS_MAYBE_HPP_INCLUDED

#include <sge/x11input/device/info/class_cast.hpp>
#include <sge/x11input/device/info/class_map.hpp>
#include <sge/x11input/device/info/class_type.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <boost/mpl/at.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace info
{

template<
	typename Class
>
fcppt::optional::reference<
	Class const
>
class_maybe(
	XIAnyClassInfo const &_info
)
{
	typedef
	fcppt::optional::reference<
		Class const
	>
	result_type;

	return
		sge::x11input::device::info::class_type(
			_info
		)
		==
		boost::mpl::at<
			sge::x11input::device::info::class_map,
			Class
		>::type::value
		?
			result_type(
				fcppt::make_cref(
					sge::x11input::device::info::class_cast<
						Class const &
					>(
						_info
					)
				)
			)
		:
			result_type()
		;
}

}
}
}
}

#endif
