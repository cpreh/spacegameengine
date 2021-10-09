//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_IMPL_OPTIONAL_KEY_SCAN_FWD_HPP_INCLUDED
#define SGE_CEGUI_IMPL_OPTIONAL_KEY_SCAN_FWD_HPP_INCLUDED

#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/InputEvent.h>
#include <fcppt/config/external_end.hpp>

namespace sge::cegui::impl
{

using optional_key_scan = fcppt::optional::object<CEGUI::Key::Scan>;

}

#endif
