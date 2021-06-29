//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_INFO_CLASS_MAYBE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_CLASS_MAYBE_HPP_INCLUDED

#include <sge/x11input/device/info/class_cast.hpp>
#include <sge/x11input/device/info/class_map.hpp>
#include <sge/x11input/device/info/class_type.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/mpl/map/at.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
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
	using
	result_type
	=
	fcppt::optional::reference<
		Class const
	>;

	return
		sge::x11input::device::info::class_type(
			_info
		)
		==
		fcppt::mpl::map::at<
			sge::x11input::device::info::class_map,
			Class
		>::value
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
