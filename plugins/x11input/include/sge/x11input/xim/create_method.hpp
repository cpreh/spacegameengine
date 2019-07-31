//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_CREATE_METHOD_HPP_INCLUDED
#define SGE_X11INPUT_XIM_CREATE_METHOD_HPP_INCLUDED

#include <sge/x11input/xim/method_unique_ptr.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace x11input
{
namespace xim
{

sge::x11input::xim::method_unique_ptr
create_method(
	fcppt::log::object &,
	awl::backends::x11::display const &
);

}
}
}

#endif
