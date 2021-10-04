//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XI_VERSION_HPP_INCLUDED
#define SGE_X11INPUT_XI_VERSION_HPP_INCLUDED

#include <awl/backends/x11/display_fwd.hpp>


namespace sge::x11input
{

[[nodiscard]]
bool
xi_version(
	awl::backends::x11::display &, // NOLINT(google-runtime-references)
	int major,
	int minor
);

}

#endif
