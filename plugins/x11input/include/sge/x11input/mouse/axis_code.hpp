//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_MOUSE_AXIS_CODE_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_AXIS_CODE_HPP_INCLUDED

#include <sge/input/mouse/axis_code_fwd.hpp>
#include <fcppt/optional_string_fwd.hpp>


namespace sge
{
namespace x11input
{
namespace mouse
{

sge::input::mouse::axis_code
axis_code(
	fcppt::optional_string const &
);

}
}
}

#endif
