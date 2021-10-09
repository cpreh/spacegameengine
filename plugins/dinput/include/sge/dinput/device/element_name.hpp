//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_DEVICE_ELEMENT_NAME_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_ELEMENT_NAME_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <fcppt/optional_string_fwd.hpp>

namespace sge
{
namespace dinput
{
namespace device
{

fcppt::optional_string element_name(DIDEVICEOBJECTINSTANCE const &);

}
}
}

#endif
