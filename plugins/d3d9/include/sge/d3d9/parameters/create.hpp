//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_PARAMETERS_CREATE_HPP_INCLUDED
#define SGE_D3D9_PARAMETERS_CREATE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/display_mode/parameters_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/window/object_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace parameters
{

D3DPRESENT_PARAMETERS
create(
    sge::renderer::pixel_format::object const &,
    sge::renderer::display_mode::parameters const &,
    awl::window::object &);

}
}
}

#endif
