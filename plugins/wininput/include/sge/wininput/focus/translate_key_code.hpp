//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WININPUT_FOCUS_TRANSLATE_KEY_CODE_HPP_INCLUDED
#define SGE_WININPUT_FOCUS_TRANSLATE_KEY_CODE_HPP_INCLUDED

#include <sge/input/key/code.hpp>
#include <awl/backends/windows/wparam.hpp>

namespace sge
{
namespace wininput
{
namespace focus
{

sge::input::key::code translate_key_code(awl::backends::windows::wparam);

}
}
}

#endif
