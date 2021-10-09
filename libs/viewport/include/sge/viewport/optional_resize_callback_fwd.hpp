//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VIEWPORT_OPTIONAL_RESIZE_CALLBACK_FWD_HPP_INCLUDED
#define SGE_VIEWPORT_OPTIONAL_RESIZE_CALLBACK_FWD_HPP_INCLUDED

#include <sge/viewport/resize_callback.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge::viewport
{

using optional_resize_callback = fcppt::optional::object<sge::viewport::resize_callback>;

}

#endif
