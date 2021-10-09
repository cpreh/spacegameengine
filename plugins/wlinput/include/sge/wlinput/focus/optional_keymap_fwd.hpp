//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_FOCUS_OPTIONAL_KEYMAP_FWD_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_OPTIONAL_KEYMAP_FWD_HPP_INCLUDED

#include <sge/wlinput/focus/keymap_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge::wlinput::focus
{

using optional_keymap = fcppt::optional::object<sge::wlinput::focus::keymap>;

}

#endif
