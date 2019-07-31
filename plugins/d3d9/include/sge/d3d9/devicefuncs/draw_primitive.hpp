//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_DEVICEFUNCS_DRAW_PRIMITIVE_HPP_INCLUDED
#define SGE_D3D9_DEVICEFUNCS_DRAW_PRIMITIVE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/primitive_type_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>


namespace sge
{
namespace d3d9
{
namespace devicefuncs
{

void
draw_primitive(
	IDirect3DDevice9 &,
	sge::renderer::vertex::first,
	sge::renderer::vertex::count,
	sge::renderer::primitive_type
);

}
}
}

#endif
