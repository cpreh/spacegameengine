//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_DISPLAY_MODE_OPTIONAL_REFRESH_RATE_FWD_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_OPTIONAL_REFRESH_RATE_FWD_HPP_INCLUDED

#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge::renderer::display_mode
{

using optional_refresh_rate = fcppt::optional::object<sge::renderer::display_mode::refresh_rate>;

}

#endif
