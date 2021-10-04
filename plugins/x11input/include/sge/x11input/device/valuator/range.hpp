//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_RANGE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_RANGE_HPP_INCLUDED

#include <sge/x11input/device/valuator/iterator.hpp>
#include <sge/x11input/device/valuator/range_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge::x11input::device::valuator
{

class range
{
public:
	explicit
	range(
		fcppt::reference<
			XIValuatorState const
		>
	);

	using
	iterator
	=
	sge::x11input::device::valuator::iterator;

	using
	const_iterator
	=
	iterator;

	[[nodiscard]]
	iterator
	begin() const;

	[[nodiscard]]
	iterator
	end() const;
private:
	fcppt::reference<
		XIValuatorState const
	> state_;
};

}

#endif
