//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_SUPPORTED_STYLES_UNIQUE_PTR_HPP_INCLUDED
#define SGE_X11INPUT_XIM_SUPPORTED_STYLES_UNIQUE_PTR_HPP_INCLUDED

#include <awl/backends/x11/deleter.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


namespace sge::x11input::xim
{

using
supported_styles_unique_ptr
=
fcppt::unique_ptr<
	XIMStyles,
	awl::backends::x11::deleter
>;

}

#endif
