//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_JOYPAD_FF_TYPE_PARAMETERS_FWD_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_FF_TYPE_PARAMETERS_FWD_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <fcppt/variant/object_fwd.hpp>

namespace sge
{
namespace dinput
{
namespace joypad
{
namespace ff
{

typedef fcppt::variant::object<DICONDITION, DIPERIODIC, DICONSTANTFORCE, DIRAMPFORCE>
    type_parameters;

}
}
}
}

#endif
