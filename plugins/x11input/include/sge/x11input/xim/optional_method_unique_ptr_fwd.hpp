//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_OPTIONAL_METHOD_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SGE_X11INPUT_XIM_OPTIONAL_METHOD_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sge/x11input/xim/method_unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge::x11input::xim
{

using
optional_method_unique_ptr
=
fcppt::optional::object<
	sge::x11input::xim::method_unique_ptr
>;

}

#endif
