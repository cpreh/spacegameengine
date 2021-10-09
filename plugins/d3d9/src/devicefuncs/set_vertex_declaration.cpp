//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_vertex_declaration.hpp>
#include <sge/d3d9/vertex/declaration.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/static_downcast.hpp>

void sge::d3d9::devicefuncs::set_vertex_declaration(
    IDirect3DDevice9 &_device, sge::renderer::vertex::declaration const &_vertex_declaration)
{
  if (_device.SetVertexDeclaration(
          &fcppt::cast::static_downcast<sge::d3d9::vertex::declaration const &>(_vertex_declaration)
               .get()) != D3D_OK)
    throw sge::renderer::exception{FCPPT_TEXT("SetVertexDeclaration() failed!")};
}
