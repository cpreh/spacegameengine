//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_GET_SUPPORTED_STYLES_HPP_INCLUDED
#define SGE_X11INPUT_XIM_GET_SUPPORTED_STYLES_HPP_INCLUDED

#include <sge/x11input/xim/method_fwd.hpp>
#include <sge/x11input/xim/supported_styles_unique_ptr.hpp>


namespace sge::x11input::xim
{

sge::x11input::xim::supported_styles_unique_ptr
get_supported_styles(
	sge::x11input::xim::method const &
);

}

#endif
