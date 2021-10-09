//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_SURFACE_COLOR_CREATE_FUNCTION_HPP_INCLUDED
#define SGE_D3D9_SURFACE_COLOR_CREATE_FUNCTION_HPP_INCLUDED

#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <fcppt/function_impl.hpp>

namespace sge
{
namespace d3d9
{
namespace surface
{

typedef fcppt::function<sge::d3d9::surface::d3d_unique_ptr()> color_create_function;

}
}
}

#endif
