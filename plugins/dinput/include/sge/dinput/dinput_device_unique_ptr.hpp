//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_DINPUT_DEVICE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_DINPUT_DINPUT_DEVICE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sge
{
namespace dinput
{

typedef fcppt::unique_ptr<IDirectInputDevice8, fcppt::com_deleter> dinput_device_unique_ptr;

}
}

#endif
