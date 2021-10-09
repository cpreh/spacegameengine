//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_DISPLAY_MODE_DESIRED_FPS_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_DESIRED_FPS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/renderer/display_mode/refresh_rate_value.hpp>

namespace sge::renderer::display_mode
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::display_mode::refresh_rate_value
desired_fps(sge::renderer::display_mode::optional_object const &);

}

#endif
