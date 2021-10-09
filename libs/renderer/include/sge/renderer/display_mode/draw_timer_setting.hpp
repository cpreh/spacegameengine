//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_DISPLAY_MODE_DRAW_TIMER_SETTING_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_DRAW_TIMER_SETTING_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <awl/timer/setting.hpp>

namespace sge::renderer::display_mode
{

SGE_RENDERER_DETAIL_SYMBOL
awl::timer::setting draw_timer_setting(sge::renderer::display_mode::refresh_rate);

}

#endif
