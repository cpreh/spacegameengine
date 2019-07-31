//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DISPLAY_MODE_FULLSCREEN_FWD_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_FULLSCREEN_FWD_HPP_INCLUDED

#include <sge/renderer/display_mode/fullscreen_desktop_fwd.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <fcppt/variant/variadic_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace display_mode
{

typedef
fcppt::variant::variadic<
	sge::renderer::display_mode::fullscreen_desktop,
	sge::renderer::display_mode::object
>
fullscreen;

}
}
}

#endif
