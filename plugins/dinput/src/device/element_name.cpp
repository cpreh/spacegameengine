//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/element_name.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

fcppt::optional_string sge::dinput::device::element_name(DIDEVICEOBJECTINSTANCE const &_data)
{
  return _data.dwSize <= offsetof(DIDEVICEOBJECTINSTANCE, tszName)
             ? fcppt::optional_string()
             : fcppt::optional_string(fcppt::string(_data.tszName));
}
