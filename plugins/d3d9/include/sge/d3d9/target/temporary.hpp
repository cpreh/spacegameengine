//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_TARGET_TEMPORARY_HPP_INCLUDED
#define SGE_D3D9_TARGET_TEMPORARY_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace d3d9
{
namespace target
{

class temporary
{
  FCPPT_NONCOPYABLE(temporary);

public:
  temporary(IDirect3DDevice9 &, sge::renderer::caps::target_surface_indices);

  ~temporary();

private:
  IDirect3DDevice9 &device_;

  sge::d3d9::surface::optional_d3d_unique_ptr const depth_stencil_surface_;

  typedef std::vector<sge::d3d9::surface::optional_d3d_unique_ptr> scoped_surface_vector;

  scoped_surface_vector color_surfaces_;
};

}
}
}

#endif
