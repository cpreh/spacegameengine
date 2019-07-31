//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_ITERATOR_BASE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_ITERATOR_BASE_HPP_INCLUDED

#include <sge/x11input/device/valuator/iterator_fwd.hpp>
#include <sge/x11input/device/valuator/pair_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace valuator
{

typedef
boost::iterator_facade<
	sge::x11input::device::valuator::iterator,
	sge::x11input::device::valuator::pair,
	std::forward_iterator_tag,
	sge::x11input::device::valuator::pair
>
iterator_base;

}
}
}
}

#endif
