//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_COMBINE_RATES_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_COMBINE_RATES_HPP_INCLUDED

#include <sge/renderer/display_mode/optional_refresh_rate_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

sge::renderer::display_mode::optional_refresh_rate
combine_rates(
	sge::renderer::display_mode::optional_refresh_rate,
	sge::renderer::display_mode::optional_refresh_rate
);

}
}
}

#endif
