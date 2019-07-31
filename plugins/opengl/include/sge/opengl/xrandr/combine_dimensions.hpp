//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_COMBINE_DIMENSIONS_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_COMBINE_DIMENSIONS_HPP_INCLUDED

#include <sge/renderer/display_mode/dimensions_fwd.hpp>
#include <sge/renderer/display_mode/optional_dimensions_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

sge::renderer::display_mode::optional_dimensions
combine_dimensions(
	sge::renderer::display_mode::optional_dimensions,
	sge::renderer::display_mode::dimensions
);

}
}
}

#endif
