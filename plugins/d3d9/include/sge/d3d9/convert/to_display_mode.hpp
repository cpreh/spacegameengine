//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_CONVERT_TO_DISPLAY_MODE_HPP_INCLUDED
#define SGE_D3D9_CONVERT_TO_DISPLAY_MODE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/display_mode/object.hpp>


namespace sge
{
namespace d3d9
{
namespace convert
{

sge::renderer::display_mode::object
to_display_mode(
	D3DDISPLAYMODE const &
);

}
}
}

#endif
