//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_ITERATOR_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_ITERATOR_HPP_INCLUDED

#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/iterator_base.hpp>
#include <sge/x11input/device/valuator/iterator_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace valuator
{

class iterator
:
	public sge::x11input::device::valuator::iterator_base
{
public:
	iterator(
		sge::x11input::device::valuator::index,
		XIValuatorState const &
	);

	void
	increment();

	bool
	equal(
		iterator const &
	) const;

	reference
	dereference() const;
private:
	void
	index_to_next_valuator();

	fcppt::reference<
		XIValuatorState const
	> state_;

	double const *valuator_;

	sge::x11input::device::valuator::index index_;

	sge::x11input::device::valuator::index length_;
};

}
}
}
}

#endif
