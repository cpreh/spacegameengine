//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_VIEWPORT_RESIZE_FUNCTION_HPP_INCLUDED
#define SGE_VIEWPORT_RESIZE_FUNCTION_HPP_INCLUDED

#include <sge/renderer/target/viewport_fwd.hpp>
#include <awl/window/event/resize_fwd.hpp>


namespace sge::viewport
{

using
resize_function
=
sge::renderer::target::viewport(
	awl::window::event::resize const &
);

}

#endif
