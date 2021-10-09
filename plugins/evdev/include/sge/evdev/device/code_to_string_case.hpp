//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE_HPP_INCLUDED

#include <fcppt/from_std_string.hpp>
#include <fcppt/optional_string.hpp>

#define SGE_EVDEV_DEVICE_CODE_TO_STRING_CASE(value) \
  case value: \
    return fcppt::optional_string(fcppt::from_std_string(#value))

#endif
