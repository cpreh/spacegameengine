//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_VALUATOR_ITERATOR_BASE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_ITERATOR_BASE_HPP_INCLUDED

#include <sge/x11input/device/valuator/iterator_fwd.hpp>
#include <sge/x11input/device/valuator/pair_fwd.hpp>
#include <fcppt/iterator/base_impl.hpp>
#include <fcppt/iterator/types.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <iterator>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::device::valuator
{

using iterator_base = fcppt::iterator::base<fcppt::iterator::types<
    sge::x11input::device::valuator::iterator,
    sge::x11input::device::valuator::pair,
    sge::x11input::device::valuator::pair,
    std::ptrdiff_t,
    std::input_iterator_tag>>;

}

#endif
