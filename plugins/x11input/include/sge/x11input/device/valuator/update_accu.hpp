//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_UPDATE_ACCU_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_UPDATE_ACCU_HPP_INCLUDED

#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge::x11input::device::valuator
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

#endif
