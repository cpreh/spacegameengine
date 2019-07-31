//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DISPLAY_MODE_OPTIONAL_FULLSCREEN_FWD_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_OPTIONAL_FULLSCREEN_FWD_HPP_INCLUDED

#include <sge/renderer/display_mode/fullscreen_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace display_mode
{

typedef
fcppt::optional::object<
	sge::renderer::display_mode::fullscreen
>
optional_fullscreen;

}
}
}

#endif
