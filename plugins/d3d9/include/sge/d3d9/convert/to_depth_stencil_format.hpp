//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_CONVERT_TO_DEPTH_STENCIL_FORMAT_HPP_INCLUDED
#define SGE_D3D9_CONVERT_TO_DEPTH_STENCIL_FORMAT_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/image/ds/format_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace convert
{

sge::image::ds::format
to_depth_stencil_format(
	D3DFORMAT
);

}
}
}

#endif
