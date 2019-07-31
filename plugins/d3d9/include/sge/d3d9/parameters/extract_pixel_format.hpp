//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_PARAMETERS_EXTRACT_PIXEL_FORMAT_HPP_INCLUDED
#define SGE_D3D9_PARAMETERS_EXTRACT_PIXEL_FORMAT_HPP_INCLUDED

#include <sge/renderer/pixel_format/object.hpp>
#include <awl/visual/object_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace parameters
{

sge::renderer::pixel_format::object
extract_pixel_format(
	awl::visual::object const &
);

}
}
}

#endif
