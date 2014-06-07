/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_X11INPUT_DEVICE_INFO_CLASS_CAST_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_CLASS_CAST_HPP_INCLUDED

#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
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
	typename Result
>
typename boost::enable_if<
	boost::mpl::contains<
		boost::mpl::vector4<
			XIButtonClassInfo,
			XIValuatorClassInfo,
			XIKeyClassInfo,
			XIScrollClassInfo
		>,
		typename std::remove_const<
			typename std::remove_reference<
				Result
			>::type
		>::type
	>,
	Result
>::type
class_cast(
	XIAnyClassInfo const &_info
)
{
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Wstrict-aliasing)

	return
		reinterpret_cast<
			Result
		>(
			_info
		);

	FCPPT_PP_POP_WARNING
}

}
}
}
}

#endif
