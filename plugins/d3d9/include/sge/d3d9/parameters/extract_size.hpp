//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_PARAMETERS_EXTRACT_SIZE_HPP_INCLUDED
#define SGE_D3D9_PARAMETERS_EXTRACT_SIZE_HPP_INCLUDED

#include <sge/renderer/screen_size_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <awl/window/object_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace parameters
{

sge::renderer::screen_size const
extract_size(
	sge::renderer::display_mode::optional_object const &,
	awl::window::object &
);

}
}
}

#endif
