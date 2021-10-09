//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/primitive_type.hpp>
#include <sge/d3d9/devicefuncs/draw_indexed_primitive.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/to_primitive_count.hpp>
#include <fcppt/text.hpp>

void sge::d3d9::devicefuncs::draw_indexed_primitive(
    IDirect3DDevice9 &_device,
    sge::renderer::vertex::first const _first_vertex,
    sge::renderer::vertex::count const _num_vertices,
    sge::renderer::primitive_type const _primitive_type,
    sge::renderer::index::first const _first_index,
    sge::renderer::index::count const _num_indices)
{
  if (_primitive_type == sge::renderer::primitive_type::point_list)
    throw sge::renderer::exception(
        FCPPT_TEXT("Rendering indexed point lists is not supported in D3D9!"));

  if (_device.DrawIndexedPrimitive(
          sge::d3d9::convert::primitive_type(_primitive_type),
          0,
          static_cast<UINT>(_first_vertex.get()),
          static_cast<UINT>(_num_vertices.get()),
          static_cast<UINT>(_first_index.get()),
          static_cast<UINT>(sge::renderer::vertex::to_primitive_count(
                                sge::renderer::vertex::count(_num_indices.get()), _primitive_type)
                                .get())) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("DrawIndexedPrimitive() failed!"));
}
