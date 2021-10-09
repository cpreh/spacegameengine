//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_SURFACE_OPTIONAL_D3D_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SGE_D3D9_SURFACE_OPTIONAL_D3D_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace surface
{

typedef fcppt::optional::object<sge::d3d9::surface::d3d_unique_ptr> optional_d3d_unique_ptr;

}
}
}

#endif
